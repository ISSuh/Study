#include <stdio.h>
#include <windows.h>
# define PSAPI_VERSION 2
#include <Psapi.h>

#define Max 1024

DWORD WINAPI Thread_Function(LPVOID ThPara){ // ������ �����尡 �����ϴ� �Լ�
	DWORD PidArray[Max], ReturnArray; // ���μ����� �������� ������ ��������, ReturnArray�� ���μ����� ID

	if (EnumProcesses(PidArray, sizeof(PidArray), &ReturnArray) == 0) // ���� ���μ����� ������ �˱�����EnumProcesses�Լ��� �̿��Ͽ� ���� ����ǰ� �ִ� ���μ����� ����(ID)�� ����
		printf("EnumProcesses() Failed\n");
	
	printf("%d\n", ReturnArray / sizeof(DWORD)); // ���μ������� ID�� ����� �迭�� ũ�⸦ ����ִ� ReturnArray ������ ũ�� DWORD�� ������ ���μ����� ������ ���

	return 0;
}

int main(){
	SYSTEMTIME time; // ���� �ý����� �ð��� �����ϱ����� ��������
	DWORD ThId = 1, ThPara = 0; // �������� Id���� �����ص� �Ķ���Ͱ��� ������ ��������
	HANDLE thread; // �����带 �����ϱ� ���� �ڵ麯�� ����

	while(1){

		GetLocalTime(&time); // ����ý����� �ð��� time������ ����
	
		printf("%d_%d_%d : %d_%d_%d : ",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond); // �ý����� �ð��� ���
		thread = CreateThread(NULL, 0, Thread_Function, (LPVOID)ThPara, 0, &ThId); // �����带 �����Ͽ� ���μ����� ������ ����
		if (thread == NULL)
			printf("CreateThread() Faild\n");

		CloseHandle(thread); // ���μ����� ������ ������, �����带 ����
		Sleep(1000); // 1�ʸ��� ����ϱ����� Sleep�Լ� ���
	}

	return 0;
}