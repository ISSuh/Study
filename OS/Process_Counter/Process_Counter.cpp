#include <stdio.h>
#include <windows.h>
# define PSAPI_VERSION 2
#include <Psapi.h>

#define Max 1024

DWORD WINAPI Thread_Function(LPVOID ThPara){ // 생성된 스레드가 동작하는 함수
	DWORD PidArray[Max], ReturnArray; // 프로세스의 정보들을 저장할 변수선언, ReturnArray는 프로세스의 ID

	if (EnumProcesses(PidArray, sizeof(PidArray), &ReturnArray) == 0) // 현재 프로세스의 갯수를 알기위해EnumProcesses함수를 이용하여 현재 실행되고 있는 프로세스의 정보(ID)를 받음
		printf("EnumProcesses() Failed\n");
	
	printf("%d\n", ReturnArray / sizeof(DWORD)); // 프로세스들의 ID가 저장된 배열의 크기를 담고있는 ReturnArray 변수를 크기 DWORD로 나누어 프로세스의 갯수를 계산

	return 0;
}

int main(){
	SYSTEMTIME time; // 현재 시스템의 시간을 저장하기위한 변수선언
	DWORD ThId = 1, ThPara = 0; // 스레드의 Id값과 전달해둘 파라미터값을 저장할 변수선언
	HANDLE thread; // 스레드를 생성하기 위해 핸들변수 선언

	while(1){

		GetLocalTime(&time); // 현재시스템의 시간을 time변수에 저장
	
		printf("%d_%d_%d : %d_%d_%d : ",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond); // 시스템의 시간을 출력
		thread = CreateThread(NULL, 0, Thread_Function, (LPVOID)ThPara, 0, &ThId); // 스레드를 생성하여 프로세스의 갯수를 구함
		if (thread == NULL)
			printf("CreateThread() Faild\n");

		CloseHandle(thread); // 프로세스의 갯수를 구한후, 스레드를 종료
		Sleep(1000); // 1초마다 출력하기위해 Sleep함수 사용
	}

	return 0;
}