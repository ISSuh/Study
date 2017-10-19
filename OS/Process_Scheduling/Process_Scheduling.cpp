#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <functional>
#include <Windows.h>
using namespace std;
#pragma warning (disable:4996)

#define MAX_LINE	1000
#define MAX_BURSTNUM		50												// �ִ� CPU,I/O Burst�� ����

struct ProcessInfo{															// CPU,I/O Burst�� ����
	int cNum;
	int iNum;
};
struct Process{																// ���μ����� ����
	int pName;
	int Arrival;
	int CPU[MAX_BURSTNUM];
	int IO[MAX_BURSTNUM];
	int C_index, I_index;

	int Wait;
	bool Switch;
	int SwitchTime;

	int state;																// ���μ����� ����, new -> ready = 3, wait -> ready = 2, running -> ready = 1  
};
struct Compare{																// Priority Queue ���� �켱������ �Ǵ� �׸��� ����ϱ� ���� ������ �����ε�
	bool operator()(Process *x, Process *y){
		if (x->CPU[x->C_index] == y->CPU[y->C_index]){						
		 if (x->Arrival == y->Arrival)										// CPU Burst�� ����, ready queue�� ���Դٸ�, ���� �켱������ ���¿� ���� ����
			return x->state < y->state;										
		else
			return  x->Arrival > y->Arrival;									// CPU Burst�� ������, �̿ܿ� ���� ���� ������ ����
		}

		else
			return x->CPU[x->C_index] > y->CPU[y->C_index];					// �Ϲ������� CPU Burst�� ���������� ����
	}
};

int Search_PNum(char *filename);											// �����ٸ��� ���μ����� ��. 05�� ������ read.form.file.cpp ����
void ReadFile(char *filename, Process *P, ProcessInfo *pInfo);				// ������ �о� ��ġ�� ����. 05�� ������ read.form.file.cpp ����
void InitProcess(Process *P, ProcessInfo *pInfo, int pNum);					// Process ����ü �ʱ�ȭ
int MaxTime(Process *P, ProcessInfo *pInfo, int pNum);						// �����층�� �ִ�ð��� ���
void P_SJF(Process *P, ProcessInfo *pInfo,int pNum);						// Preemptive SJF �����층

int main(int argc, char** argv){
	if (argc < 1){ printf("Error: Lack Param\n"); exit(0); }
	else if (argc > 3){ printf("Error: Many Param.\n"); exit(0); }

	int pNum = Search_PNum(argv[1]),WaitAvg = 0;							// ������ �о� ���μ����� ���� �˻�
	ProcessInfo *pInfo = (ProcessInfo*)malloc(sizeof(ProcessInfo) * pNum);	// �� ���μ����� CPU Burst�� I/O Burst�� ���� ������ ����ü�� ���μ����� ����ŭ �����Ҵ�
	Process *P = (Process*)malloc(sizeof(Process) * pNum);					// ���μ����� ������ ������ ����ü�� ���μ����� �� ��ŭ �����Ҵ�

	InitProcess(P,pInfo,pNum);												// Process�� ProcessInfo ����ü �ʱ�ȭ
	ReadFile(argv[1],P,pInfo);												// ������ �о� Process ����ü�� ��ġ ����
	P_SJF(P, pInfo, pNum);													// P_SJF�����층�Ͽ� Waiting time�� ���

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
	Process *Select = NULL, *temp = NULL;									// ���õ� Process�� ������ ����
	priority_queue<Process *, vector<Process *>, Compare> PQ;				// Priority Queue ����

	while (time < maxTime){													// �ѹ� ������ 1�ʷ� �����ϰ�, �ִ�ð����� ����
		//printf("[%d]	", time);

		for (int i = 0; i < pNum; i++){										// ���μ����� �����ߴٸ�, ť�� ���� 
			if ((P + i)->Arrival == time && (P + i)->C_index < (pInfo + i)->cNum){		
				PQ.push((P + i));
				//printf(" <P[%d] in> ", (P + i)->pName);
			}

			if (Select != NULL && Select->CPU[Select->C_index] != 0 && Select->pName != PQ.top()->pName){		// ���� ���õ� ���μ����� ť�� ���� ���� ���õ� ���μ����� �ٸ��ٸ��, CPU Burst�� 0�� �ƴҶ�,
				Select->Switch = TRUE;																			// �̴� ���μ����� ��ü�� ������ �Ǵ�
				Select->SwitchTime = time;
				Select->state = 1;																				// �̶�, running -> ready�� ���°� ����Ǿ����Ƿ�, �켱������ ���� ������ 1�� ���� 
			}
		}

		if (PQ.size() != 0){
			temp = Select;
			Select = PQ.top();												// ť�� ���� �տ� �ִ°��� �ּ� CPU Burst�̹Ƿ� �̸� ����

			if (temp != Select && !Select->Switch)		
				Select->Wait += time - Select->Arrival;						// ���ʷ� ���� �Ǿ�����, waiting time ���

			else if (Select->Switch){										// Preemptive �� ���μ����� �ٽ� ���õǾ��ٸ�, �̶��� waiting time ���
				Select->Wait += time - Select->SwitchTime;
				Select->Switch = FALSE;
				Select->SwitchTime = 0;
			}
		}

		if ((Select != NULL)){
			if (Select->CPU[Select->C_index] == 0){							// CPU Burst�����ٸ�,
				PQ.pop();													// �ش� ���μ����� ������,
				Select->C_index++;											// CPU Burst�� ����Ű�� �ִ� �ε����� ������Ŵ

				if ((pInfo + (Select->pName))->iNum > 0){					// ���õ� ���μ����� I/O Burst�� 1�� �̻��̶��,
					Select->Arrival = time + Select->IO[Select->I_index];	// �����ð��� I/O Burst �ķ� �����Ͽ� I/O Burst �Ŀ� �ٽ� �������� ��	
					Select->I_index++;										// I/O Burst�� ����Ű�� �ִ� �ε����� ������Ŵ
					Select->state = 2;										// I/O�� ������ �ٽ� ready queue�� �����Ƿ� ���¸� 2�� ����
				}

				if (PQ.size() != 0){
					Select = PQ.top();										// ���� ���μ�����  I/OȤ�� ���� �Ǿ����Ƿ� ���� ���μ����� ����
																			// �̶���  waiting time ���
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

		if ((Select != NULL)){												// ���õ� ���μ�����  CPU Burst�� 1�� ����
			if (Select->CPU[Select->C_index] > 0){
				Select->CPU[Select->C_index]--;
				Select->state = 3;
			}
		}

		if (PQ.size() != 0)													// ������ ������ ť�� ���� �ٽ� ����
			PQ.pop();

		if (Select != NULL)
			PQ.push(Select);

		//printf("\n");
		time++;
	}
}
