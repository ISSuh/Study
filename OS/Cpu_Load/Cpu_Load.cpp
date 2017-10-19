#include <stdio.h>
#include <windows.h>
#include <Pdh.h>
#pragma comment(lib,"Pdh.lib") // 

double Fs_arr[5],Ts_arr[10],Ffs_arr[15];
double Fs_ave(int i);
double Ts_ave(int j);
double Ffs_ave(int k);

int main(){
	system("mode con:lines=40 cols=125"); // �ܼ�âũ�� ����

	int count=0,i=0,j=0,k=0;
	SYSTEMTIME time; // ���� �ý����� �ð��� �����ϱ����� ��������
	SYSTEM_INFO Sys; // cpu�� ���� �˱����� ��������
	PDH_HQUERY CQuery; // ���ɵ����͸� �ޱ����� ��������
	PDH_HCOUNTER Total_CPU;// �ڵ� ���� ����
	PDH_FMT_COUNTERVALUE Val; // ������ �����͸� �����ϱ����� ��������

	PdhOpenQuery(NULL, NULL, &CQuery); // ���ɵ����͸� �ޱ����� ��������
	PdhAddCounter(CQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &Total_CPU); // CPU�� ��ü �������� ���ϰ� �ڵ��� �߰�
	PdhCollectQueryData(CQuery); // ���ɵ����͸� ����
	
	GetSystemInfo(&Sys); //�ý������� ����
	
	printf("Numer of CPUs : %d\n", Sys.dwNumberOfProcessors); // ���� �ý����� ���μ��� �������
	while (1){

		GetLocalTime(&time); // ����ý����� �ð��� time������ ����
		printf("%4d %d.%d.%d %d:%d:%2d  : ", count, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond); // �ð����

		PdhCollectQueryData(CQuery); // ���ɵ����͸� ����
		PdhGetFormattedCounterValue(Total_CPU, PDH_FMT_DOUBLE, NULL, &Val); // ������ ���ɵ����Ϳ��� �����͸� double���� ������������ �Ѱܹ���

		printf("[CPU Load: %.2f%%] ", Val.doubleValue); // CPU ���Ϸ� ���

		Fs_arr[i] = Ts_arr[j] = Ffs_arr[j] = Val.doubleValue; // ���� cpu������ �� �迭�� ����

		if (count >= 5 && count < 10)
			printf("[5Sec ave: %.2f%%]\n", Fs_ave(i));
		else if (count >= 10 && count < 15)
			printf("[5Sec ave: %.2f%%] [10Sec ave: %.2f%%]\n", Fs_ave(i), Ts_ave(j));
		else if (count >= 15)
			printf("[5Sec ave: %.2f%%] [10Sec ave: %.2f%%] [15Sec ave: %.2f%%]\n", Fs_ave(i), Ts_ave(j), Ffs_ave(k));
		else
			printf("\n"); // 5��,10��,15�� ���� ��� ���Ϸ��� ���ϰ� ���

		count++; i++; j++; k++; // ��ü Ƚ��, �� �迭�� �ε������� ����

		if (i == 5) i = 0; 
		if (j == 10) j = 0;
		if (k == 15) k = 0; // 5��,10��,15�ʸ��� ����� ���ϱ� ���� �ε����� �ʰ��ϸ� 0���� ���ο�� ����

		Sleep(1000); 
	}

	return 0;
}

double Fs_ave(int i){
	double sum=0;
	for (int x = 0; x < 5; x++)
		sum += Fs_arr[x];
	return sum/5;
}

double Ts_ave(int j){
	double sum = 0;
	for (int x = 0; x < 10; x++)
		sum += Ts_arr[x];
	return sum / 10;
}

double Ffs_ave(int k){
	double sum = 0;
	for (int x = 0; x < 15; x++)
		sum += Ffs_arr[x];
	return sum / 15;
}   // 5��,10��,15�� ���� �迭�� ����� �������� ����� ����
