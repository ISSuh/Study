#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

enum { REQUEST_ARK_H_ADR_SUCCESS, ARK_H_Reply_FAIL, REQUEST_H_ADR_FAIL, IN_DATA };

#define MAX_TIME	 5
#define MAX_ATTEMP	 3
#define TABLE_NUM	 5

struct Table{
	char State;
	int QNumber;
	int Time;
	int Attemp;
	int Protocol_ADR;
	int Hadware_ADR;
};

double randomDouble();
int randomInt(int Start, int End);
void PrintTable(Table *T);
void InitTable(Table *T);
void InputData(Table *T, int index, int Qnum);
void DeleteEntry(Table *T, int index);
void GetHardwareADR(Table * T,int index);
int IOEvent();
int RAEvent();
void CacheControl(Table *T, int RE_AR_Event);

int main(){
	srand(GetTickCount());

	int time = 0,INOUT_Event = 0,RE_AR_Event = 0,Qnum = 1;
	Table T[TABLE_NUM];
	InitTable(T);

	while (1){
		printf("Cache Table at %d Second \n", time);
		printf("Occur Event : ");
	
		INOUT_Event = IOEvent();
		
		if (INOUT_Event == IN_DATA){
			for (int i = 0; i < TABLE_NUM; i++){
				if ((T + i)->State == 'F'){
					InputData(T, i, Qnum);
					printf("Input Data in Q[%d] \n", (T + i)->QNumber);
					Qnum++;
					break;
				}
			}
		}

		else
			printf("\n");

		printf("\n");

		CacheControl(T, INOUT_Event);
		PrintTable(T);

		INOUT_Event = 0;

		printf("\n");
		Sleep(2000);
		time++;
	}
}

double randomDouble(){
	return (double)rand() / RAND_MAX;
}
int randomInt(int Start, int End){
	return rand() % (End - Start + 1) + Start;
}
void PrintTable(Table *T){
	printf("\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");
	printf("State	|	Queue	|	Attemp	|	Time-out	|	Protocol-ADR	|	Hadware-ADR	|\n");
	printf("----------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < TABLE_NUM; i++)
		printf(" %c	|	%d	|	%d	|	%2d		|	%d		|	%4d		|\n", (T + i)->State, (T + i)->QNumber, (T + i)->Attemp, (T + i)->Time, (T + i)->Protocol_ADR, (T + i)->Hadware_ADR);

	printf("----------------------------------------------------------------------------------------------------------------\n");
	printf("\n");
}
void InitTable(Table *T){
	for (int i = 0; i < TABLE_NUM; i++){
		(T + i)->Time = NULL;		(T + i)->Attemp = NULL;
		(T + i)->State = 'F';		(T + i)->QNumber = NULL;
		(T + i)->Protocol_ADR = NULL;
		(T + i)->Hadware_ADR = NULL;
	}
}
void InputData(Table *T, int index, int Qnum){
	(T + index)->Time = 0;	(T + index)->Attemp = 0;
	(T + index)->State = 'P';		(T + index)->QNumber = Qnum;
	(T + index)->Protocol_ADR = randomInt(0,100);
	(T + index)->Hadware_ADR = 0;
}
void DeleteEntry(Table *T, int index){
	(T + index)->Time = 0;		(T + index)->Attemp = 0;
	(T + index)->State = 'F';		(T + index)->QNumber = 0;
	(T + index)->Protocol_ADR = 0;
	(T + index)->Hadware_ADR = 0;
}
void GetHardwareADR(Table * T, int index){
	(T + index)->Hadware_ADR = randomInt(100,1000);
}
int IOEvent(){
	int E = 0;

	if (randomDouble() <= 0.5)
		E = IN_DATA;

	return E;
}
int RAEvent(){
	int E = 0;

	if (randomDouble() <= 0.3)
		E = REQUEST_ARK_H_ADR_SUCCESS;

	else{
		if (randomDouble() <= 0.5)
			E = REQUEST_H_ADR_FAIL;
		else
			E = ARK_H_Reply_FAIL;
	}
	return E;
}
void CacheControl(Table *T, int RE_AR_Event){
	for (int i = 0; i < TABLE_NUM; i++){

		printf("Table[%d] Event : ",i+1);

		switch ((T + i)->State){

		case 'P':
			RE_AR_Event = RAEvent();

			if ((T + i)->Attemp == 5){
				printf("Over Attemp. Delete Q[%d]", (T + i)->QNumber);
				DeleteEntry(T, i);
			}

			else{
				printf("Send Request Packet | ");

				switch (RE_AR_Event){

				case REQUEST_ARK_H_ADR_SUCCESS:
					GetHardwareADR(T, i);
					(T + i)->State = 'R';
					(T + i)->Attemp = 0;
					(T + i)->Time = MAX_TIME;
					printf(" Get Hardware ADR ");
					break;

				case REQUEST_H_ADR_FAIL:
					(T + i)->Attemp++;
					printf(" Request Packet Error ");
					break;

				case  ARK_H_Reply_FAIL:
					(T + i)->Attemp++;
					printf(" Reply Packet Error ");
					break;
				}
			}

			break;

		case 'R':
			if ((T + i)->Time != 0)
				(T + i)->Time--;

			else{
				printf("Over Time. Delete Q[%d]	", (T + i)->QNumber);
				DeleteEntry(T, i);
			}

			break;
		}
	
		printf("\n");
	}
}
