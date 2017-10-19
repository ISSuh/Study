#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#define PSAPI_VERSION 2
#include <Psapi.h>
#pragma warning (disable:4996)

#define Max 1024

BOOL GetProcessList(int ppid, int depth, bool Orphan); // 트로세스 트리를 출력하는 함수
BOOL FindOrphan(PROCESSENTRY32 processInfo); // 고아 프로세스를 확인하기 위한 함수

int count = 2;
bool flag = TRUE;

int main(void)
{
	int NumProcess;
	DWORD PidArray[Max], ReturnArray;
	
	EnumProcesses(PidArray, sizeof(PidArray), &ReturnArray); // 현재 프로세스의 갯수를 알기위해EnumProcesses함수를 이용하여 현재 실행되고 있는 프로세스의 정보(ID)를 받음
	NumProcess = ReturnArray / sizeof(DWORD); // 현재 프로세스의 갯수 연산
	printf(" ############### Process Tree ###############\n");
	printf("Number of Running Processes = %d\n", NumProcess);
	printf("EX : ProcessName (PID) (PPID)\n");

	GetProcessList(0,1,TRUE); // 프로세스 트리를 출력
	return 0;
}

BOOL GetProcessList(int ppid, int depth, bool Orphan)
{
	HANDLE hProcessSnap; // 현재 프로세스 스냅샷을 저장하기위한 변수
	PROCESSENTRY32 processInfo; // 프로세스들의 정보가 저장될 구조체변수

	if ((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE){ // 현재 프로세스의 스냅샷을 저장 
		return FALSE;
	}

	processInfo.dwSize = sizeof(PROCESSENTRY32); // 저장된 스냅샷대로 프로세스의 정보를 저장하기위해 processInfo변수의 사이즈를 넘겨줌

	if (!Process32First(hProcessSnap, &processInfo)){ // 스냅샷 처음의 프로세스
		CloseHandle(hProcessSnap);
		return FALSE;
	}	

	if (flag){ // 처음 프로세스인 System Process 를 따로 먼저 출력
		printf("  1 ");
		_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.dwSize);
		flag = FALSE;
	}
	
	do{ // 재귀함수를 통하여 프로세스 트리를 만듬
		if (ppid == processInfo.th32ParentProcessID && ppid != processInfo.th32ProcessID){ // 현재 프로세스의 자식프로세스를 찾아 출력
			printf("%2d ",count);

			for (int i = 0; i < depth; i++) // depth만큼 공백출력
				printf("|	");

			_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.th32ParentProcessID);

			count++;
			GetProcessList(processInfo.th32ProcessID, depth + 1, FALSE); // 현재 pid를 이용해 자식 프로세스를 찾도록 인자를 넘겨주고, 공백을 더함 
		}																// 또한 고아 프로세스가 아니므로 false를 넘겨줌
	
		else if (FindOrphan(processInfo) && Orphan == TRUE){ // 고아 프로세스를 따로 찾아, 출력
			printf("%2d |	", count);

			_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.th32ParentProcessID);

			count++;
			GetProcessList(processInfo.th32ProcessID, 2, FALSE); // 재귀함수로 해당 고아 프로세스의 자식 프로세스를 찾음
		}
	} while (Process32Next(hProcessSnap, &processInfo)); // 스냅샷의 저장된 순서대로 다음 프로세스로 넘어감

	CloseHandle(hProcessSnap);
	return TRUE;
}

BOOL FindOrphan(PROCESSENTRY32 processInfo){ // 넘겨받은 프로세스의 부모프로세스의 부모프로세스를 찾는다.
											//  만약 현재 존재하지 않은 프로세스, 즉 processInfo가 고아 프로세스이면, 		
	HANDLE hProcessSnap;					// true를 넘겨주고, 존재하고 있다면 false를 넘겨준다.
	PROCESSENTRY32 proc;					

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE){
		return FALSE;
	}

	proc.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &proc)){
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	do{
		if (proc.th32ProcessID == processInfo.th32ParentProcessID)
			return FALSE;
	} while (Process32Next(hProcessSnap, &proc));

	CloseHandle(hProcessSnap);
	return TRUE;
}