#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <functional>
#include <Windows.h>
using namespace std;
#pragma warning (disable:4996)

#define MAX_LINE	1000
#define MAX_BURSTNUM		50												// 최대 CPU,I/O Burst의 갯수

struct ProcessInfo{															// CPU,I/O Burst의 갯수
	int cNum;
	int iNum;
};
struct Process{																// 프로세스의 정보
	int pName;
	int Arrival;
	int CPU[MAX_BURSTNUM];
	int IO[MAX_BURSTNUM];
	int C_index, I_index;

	int Wait;
	bool Switch;
	int SwitchTime;

	int state;																// 프로세스의 상태, new -> ready = 3, wait -> ready = 2, running -> ready = 1  
};
struct Compare{																// Priority Queue 에서 우선순위가 되는 항목을 계산하기 위한 연산자 오버로딩
	bool operator()(Process *x, Process *y){
		if (x->CPU[x->C_index] == y->CPU[y->C_index]){						
		 if (x->Arrival == y->Arrival)										// CPU Burst가 같고, ready queue에 들어왔다면, 높은 우선순위의 상태에 따라 결정
			return x->state < y->state;										
		else
			return  x->Arrival > y->Arrival;									// CPU Burst가 같을때, 이외엔 먼저 들어온 순으로 결정
		}

		else
			return x->CPU[x->C_index] > y->CPU[y->C_index];					// 일반적으론 CPU Burst가 적은순으로 결정
	}
};

int Search_PNum(char *filename);											// 스케줄링할 프로세스의 수. 05번 과제의 read.form.file.cpp 참고
void ReadFile(char *filename, Process *P, ProcessInfo *pInfo);				// 파일을 읽어 수치를 저장. 05번 과제의 read.form.file.cpp 참고
void InitProcess(Process *P, ProcessInfo *pInfo, int pNum);					// Process 구조체 초기화
int MaxTime(Process *P, ProcessInfo *pInfo, int pNum);						// 스케쥴링의 최대시간을 계산
void P_SJF(Process *P, ProcessInfo *pInfo,int pNum);						// Preemptive SJF 스케쥴링

int main(int argc, char** argv){
	if (argc < 1){ printf("Error: Lack Param\n"); exit(0); }
	else if (argc > 3){ printf("Error: Many Param.\n"); exit(0); }

	int pNum = Search_PNum(argv[1]),WaitAvg = 0;							// 파일을 읽어 프로세스의 수를 검색
	ProcessInfo *pInfo = (ProcessInfo*)malloc(sizeof(ProcessInfo) * pNum);	// 각 프로세스의 CPU Burst와 I/O Burst의 수를 저장할 구조체를 프로세스의 수만큼 동적할당
	Process *P = (Process*)malloc(sizeof(Process) * pNum);					// 프로세스의 정보를 저장할 구조체를 프로세스의 수 만큼 동적할당

	InitProcess(P,pInfo,pNum);												// Process와 ProcessInfo 구조체 초기화
	ReadFile(argv[1],P,pInfo);												// 파일을 읽어 Process 구조체에 수치 저장
	P_SJF(P, pInfo, pNum);													// P_SJF스케쥴링하여 Waiting time을 계산

	printf("\n\n");
	printf("Process : Waiting Time\n");
	printf("-----------------------------------------------------\n");

	for (int k = 0; k < pNum; k++){
		WaitAvg += (P + k)->Wait;
		printf("P[%d]	: %3d\n", (P + k)->pName, (P + k)->Wait);
	}

	printf("-----------------------------------------------------\n");

	printf("Average Waiting Time : %.2f\n", (double)WaitAvg / pNum);

	free(P);	free(pInfo);	
}

int Search_PNum(char *filename){
	int  PNum = 0;
	char line[MAX_LINE], *tok;
	FILE *fp;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }
	while (fgets(line, MAX_LINE, fp)){
		tok = strtok(line, ":");
		PNum++;
	}
	fclose(fp);
	return PNum;
}

void ReadFile(char *filename, Process *P, ProcessInfo *pInfo){
	int i = 0, k = 0;
	char line[MAX_LINE], *tok;
	FILE *fp;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }
	while (fgets(line, MAX_LINE, fp)){		
		tok = strtok(line, ":");		
		do
		{
			if (i == 0){
				(P + k)->pName = atoi(tok) + k;
				printf("P[%d] ", (P + k)->pName);
			}
			else if (i == 1){
				(P + k)->Arrival = atoi(tok);
				printf("ARRIVAL : %d ", (P + k)->Arrival);
			}
			else if (i >= 2 && i % 2 == 0){
				(P + k)->CPU[i / 2 - 1] = atoi(tok);
				printf("CPU Bust : %d ", atoi(tok));
			}
			else  {
				(P + k)->IO[i / 2 - 1] = atoi(tok);
				printf("I/O Bust : %d ", atoi(tok));
			}
			i++;
		} while (tok = strtok(NULL, ":"));

		(pInfo + k)->cNum = (i - 2) / 2 + 1;
		(pInfo + k)->iNum = (i - 2) / 2;

		i = 0;	k++;
		printf("\n");
	}
	fclose(fp);
}

void InitProcess(Process *P, ProcessInfo *pInfo, int pNum){
	for (int k = 0; k < pNum; k++){
		(pInfo + k)->cNum = 0;	(pInfo + k)->iNum = 0;
		(P + k)->Arrival = 0;		(P + k)->pName = 0;
		(P + k)->C_index = 0;		(P + k)->I_index = 0;
		(P + k)->Wait = 0;			(P + k)->Switch = FALSE;
		(P + k)->SwitchTime = 0;	(P + k)->state = 3;

		for (int i = 0; i < MAX_BURSTNUM; i++){
			(P + k)->CPU[i] = NULL;
			(P + k)->IO[i] = NULL;
		}
	}
}

int MaxTime(Process *P, ProcessInfo *pInfo, int pNum){
	int max = 0;

	for (int k = 0; k < pNum; k++){
		for (int i = 0; i < (pInfo + k)->cNum; i++)
			max += (P + k)->CPU[i];
		for (int i = 0; i < (pInfo + k)->iNum; i++)
			max += (P + k)->IO[i];
	}

	return max;
}

void P_SJF(Process *P, ProcessInfo *pInfo, int pNum){
	int time = 0;
	int maxTime = MaxTime(P, pInfo, pNum);
	Process *Select = NULL, *temp = NULL;									// 선택될 Process를 저장할 변수
	priority_queue<Process *, vector<Process *>, Compare> PQ;				// Priority Queue 생성

	while (time < maxTime){													// 한번 루프를 1초로 가정하고, 최대시간동안 루프
		//printf("[%d]	", time);

		for (int i = 0; i < pNum; i++){										// 프로세스가 도착했다면, 큐에 저장 
			if ((P + i)->Arrival == time && (P + i)->C_index < (pInfo + i)->cNum){		
				PQ.push((P + i));
				//printf(" <P[%d] in> ", (P + i)->pName);
			}

			if (Select != NULL && Select->CPU[Select->C_index] != 0 && Select->pName != PQ.top()->pName){		// 현재 선택된 프로세스가 큐에 가장 위에 선택된 프로세스와 다르다면고, CPU Burst가 0이 아닐때,
				Select->Switch = TRUE;																			// 이는 프로세스가 교체된 것으로 판단
				Select->SwitchTime = time;
				Select->state = 1;																				// 이때, running -> ready로 상태가 변경되었으므로, 우선순위는 가장 낮으니 1로 변경 
			}
		}

		if (PQ.size() != 0){
			temp = Select;
			Select = PQ.top();												// 큐의 가장 앞에 있는것이 최소 CPU Burst이므로 이를 선택

			if (temp != Select && !Select->Switch)		
				Select->Wait += time - Select->Arrival;						// 최초로 선택 되었을때, waiting time 계산

			else if (Select->Switch){										// Preemptive 된 프로세스가 다시 선택되었다면, 이때의 waiting time 계산
				Select->Wait += time - Select->SwitchTime;
				Select->Switch = FALSE;
				Select->SwitchTime = 0;
			}
		}

		if ((Select != NULL)){
			if (Select->CPU[Select->C_index] == 0){							// CPU Burst끝났다면,
				PQ.pop();													// 해당 프로세스를 빼내고,
				Select->C_index++;											// CPU Burst를 가리키고 있던 인덱스를 증가시킴

				if ((pInfo + (Select->pName))->iNum > 0){					// 선택된 프로세스의 I/O Burst가 1개 이상이라면,
					Select->Arrival = time + Select->IO[Select->I_index];	// 도착시간을 I/O Burst 후로 변경하여 I/O Burst 후에 다시 들어오도록 함	
					Select->I_index++;										// I/O Burst를 가리키고 있던 인덱스를 증가시킴
					Select->state = 2;										// I/O를 끝내고 다시 ready queue로 들어오므로 상태를 2로 변경
				}

				if (PQ.size() != 0){
					Select = PQ.top();										// 전의 프로세스가  I/O혹은 종료 되었으므로 다음 프로세스를 선택
																			// 이때의  waiting time 계산
					if (!Select->Switch)
						Select->Wait += time - Select->Arrival;

					else if (Select->Switch){
						Select->Wait += time - Select->SwitchTime;
						Select->Switch = FALSE;
						Select->SwitchTime = 0;
					}
				}
			}
		}

		/*if (PQ.size() != 0)
			printf("--> Select P[%d]  %d", Select->pName, Select->CPU[Select->C_index]);
		
		else{
			printf(" ");
			Select = NULL;
		}*/

		if ((Select != NULL)){												// 선택된 프로세스의  CPU Burst를 1씩 감소
			if (Select->CPU[Select->C_index] > 0){
				Select->CPU[Select->C_index]--;
				Select->state = 3;
			}
		}

		if (PQ.size() != 0)													// 현재의 정보를 큐에 빼고 다시 넣음
			PQ.pop();

		if (Select != NULL)
			PQ.push(Select);

		//printf("\n");
		time++;
	}
}
