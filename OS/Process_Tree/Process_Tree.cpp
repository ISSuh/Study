#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <stdio.h>
#define PSAPI_VERSION 2
#include <Psapi.h>
#pragma warning (disable:4996)

#define Max 1024

BOOL GetProcessList(int ppid, int depth, bool Orphan); // Ʈ�μ��� Ʈ���� ����ϴ� �Լ�
BOOL FindOrphan(PROCESSENTRY32 processInfo); // ��� ���μ����� Ȯ���ϱ� ���� �Լ�

int count = 2;
bool flag = TRUE;

int main(void)
{
	int NumProcess;
	DWORD PidArray[Max], ReturnArray;
	
	EnumProcesses(PidArray, sizeof(PidArray), &ReturnArray); // ���� ���μ����� ������ �˱�����EnumProcesses�Լ��� �̿��Ͽ� ���� ����ǰ� �ִ� ���μ����� ����(ID)�� ����
	NumProcess = ReturnArray / sizeof(DWORD); // ���� ���μ����� ���� ����
	printf(" ############### Process Tree ###############\n");
	printf("Number of Running Processes = %d\n", NumProcess);
	printf("EX : ProcessName (PID) (PPID)\n");

	GetProcessList(0,1,TRUE); // ���μ��� Ʈ���� ���
	return 0;
}

BOOL GetProcessList(int ppid, int depth, bool Orphan)
{
	HANDLE hProcessSnap; // ���� ���μ��� �������� �����ϱ����� ����
	PROCESSENTRY32 processInfo; // ���μ������� ������ ����� ����ü����

	if ((hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) == INVALID_HANDLE_VALUE){ // ���� ���μ����� �������� ���� 
		return FALSE;
	}

	processInfo.dwSize = sizeof(PROCESSENTRY32); // ����� ��������� ���μ����� ������ �����ϱ����� processInfo������ ����� �Ѱ���

	if (!Process32First(hProcessSnap, &processInfo)){ // ������ ó���� ���μ���
		CloseHandle(hProcessSnap);
		return FALSE;
	}	

	if (flag){ // ó�� ���μ����� System Process �� ���� ���� ���
		printf("  1 ");
		_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.dwSize);
		flag = FALSE;
	}
	
	do{ // ����Լ��� ���Ͽ� ���μ��� Ʈ���� ����
		if (ppid == processInfo.th32ParentProcessID && ppid != processInfo.th32ProcessID){ // ���� ���μ����� �ڽ����μ����� ã�� ���
			printf("%2d ",count);

			for (int i = 0; i < depth; i++) // depth��ŭ �������
				printf("|	");

			_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.th32ParentProcessID);

			count++;
			GetProcessList(processInfo.th32ProcessID, depth + 1, FALSE); // ���� pid�� �̿��� �ڽ� ���μ����� ã���� ���ڸ� �Ѱ��ְ�, ������ ���� 
		}																// ���� ��� ���μ����� �ƴϹǷ� false�� �Ѱ���
	
		else if (FindOrphan(processInfo) && Orphan == TRUE){ // ��� ���μ����� ���� ã��, ���
			printf("%2d |	", count);

			_tprintf(TEXT("+-%s (%d) (%d)\n "), processInfo.szExeFile, processInfo.th32ProcessID, processInfo.th32ParentProcessID);

			count++;
			GetProcessList(processInfo.th32ProcessID, 2, FALSE); // ����Լ��� �ش� ��� ���μ����� �ڽ� ���μ����� ã��
		}
	} while (Process32Next(hProcessSnap, &processInfo)); // �������� ����� ������� ���� ���μ����� �Ѿ

	CloseHandle(hProcessSnap);
	return TRUE;
}

BOOL FindOrphan(PROCESSENTRY32 processInfo){ // �Ѱܹ��� ���μ����� �θ����μ����� �θ����μ����� ã�´�.
											//  ���� ���� �������� ���� ���μ���, �� processInfo�� ��� ���μ����̸�, 		
	HANDLE hProcessSnap;					// true�� �Ѱ��ְ�, �����ϰ� �ִٸ� false�� �Ѱ��ش�.
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