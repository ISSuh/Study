#include <stdio.h>
#include <windows.h>
#include <Pdh.h>
#pragma comment(lib,"Pdh.lib") // 

double Fs_arr[5],Ts_arr[10],Ffs_arr[15];
double Fs_ave(int i);
double Ts_ave(int j);
double Ffs_ave(int k);

int main(){
	system("mode con:lines=40 cols=125"); // 콘솔창크기 변경

	int count=0,i=0,j=0,k=0;
	SYSTEMTIME time; // 현재 시스템의 시간을 저장하기위한 변수선언
	SYSTEM_INFO Sys; // cpu의 수를 알기위한 변수선언
	PDH_HQUERY CQuery; // 성능데이터를 받기위한 변수선언
	PDH_HCOUNTER Total_CPU;// 핸들 변수 선언
	PDH_FMT_COUNTERVALUE Val; // 수집한 데이터를 저장하기위한 변수선언

	PdhOpenQuery(NULL, NULL, &CQuery); // 성능데이터를 받기위한 쿼리생성
	PdhAddCounter(CQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &Total_CPU); // CPU의 전체 부하율을 구하고 핸들을 추가
	PdhCollectQueryData(CQuery); // 성능데이터를 수집
	
	GetSystemInfo(&Sys); //시스템정보 수집
	
	printf("Numer of CPUs : %d\n", Sys.dwNumberOfProcessors); // 현재 시스템의 프로세서 갯수출력
	while (1){

		GetLocalTime(&time); // 현재시스템의 시간을 time변수에 저장
		printf("%4d %d.%d.%d %d:%d:%2d  : ", count, time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond); // 시간출력

		PdhCollectQueryData(CQuery); // 성능데이터를 수집
		PdhGetFormattedCounterValue(Total_CPU, PDH_FMT_DOUBLE, NULL, &Val); // 수집한 성능데이터에서 데이터를 double형의 데이터형으로 넘겨받음

		printf("[CPU Load: %.2f%%] ", Val.doubleValue); // CPU 부하량 출력

		Fs_arr[i] = Ts_arr[j] = Ffs_arr[j] = Val.doubleValue; // 현재 cpu정보를 각 배열에 저장

		if (count >= 5 && count < 10)
			printf("[5Sec ave: %.2f%%]\n", Fs_ave(i));
		else if (count >= 10 && count < 15)
			printf("[5Sec ave: %.2f%%] [10Sec ave: %.2f%%]\n", Fs_ave(i), Ts_ave(j));
		else if (count >= 15)
			printf("[5Sec ave: %.2f%%] [10Sec ave: %.2f%%] [15Sec ave: %.2f%%]\n", Fs_ave(i), Ts_ave(j), Ffs_ave(k));
		else
			printf("\n"); // 5초,10초,15초 마다 평균 부하률을 구하고 출력

		count++; i++; j++; k++; // 전체 횟수, 각 배열의 인덱스값을 증가

		if (i == 5) i = 0; 
		if (j == 10) j = 0;
		if (k == 15) k = 0; // 5초,10초,15초마다 평균을 구하기 위해 인덱스를 초과하면 0부터 새로운값을 저장

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
}   // 5초,10초,15초 마다 배열에 저장된 부하율의 평균을 구함
