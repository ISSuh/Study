#include <stdio.h>
#include <queue>
#pragma warning (disable:4996)
using namespace std;

#define MAX_LINE	1000
#define DELIM		" \r\t"

struct Process {													// 프로세스의 정보 구조체
	int Pnum;
	int *MAX;
	int *ALLOCATION;
	int *NEED;
};

int m, n;															// 리소스의 수, 프로세스의 수

void FindNum(char *filename);										// 리소스의 수와 프로세스의 수를 구함
void ReadFile(char *filename, Process *P, int *Available);			// 파일을 읽어 정보를 저장
Process *InitProcess();												// 구조체 초기화
int *InitAvailable();												// Available배열 초기화
bool *InintFinish();												// Finish배열 초기화
void GetNeed(Process *P);											// 각 프로세스의 NEED를 구함
bool SafetyCheck(bool *Finish);										// safe상태인지 검사
bool Need_WorkCheck(Process P, int *Work);							// Need[i] <= Work[i] 인지 검사
void PrintQ(queue<int> Q);											// safety 순서대로 저장후, 이를 출력

int main(int argc, char** argv){
	if (argc < 1){ printf("Error: Lack Param\n"); exit(0); }
	else if (argc > 3){ printf("Error: Many Param.\n"); exit(0); }

	Process *Pr = NULL;
	int *Available = NULL;
	int *Work;
	bool *Finish, flag;
	queue<int> Q;

	FindNum(argv[1]);

	Finish = InintFinish();
	Pr = InitProcess();
	Available = InitAvailable();

	ReadFile(argv[1], Pr, Available);
	GetNeed(Pr);

	Work = Available;

	printf("\n\n---------------------------------------------------------------------------\n\n");

	for (int k = 0; k < n; k++){										// 프로세스의 n만큼 두번의 루프
		for (int i = 0; i < n; i++){
			if (Finish[i] == false && Need_WorkCheck(*(Pr + i), Work)){	// Finish[i]가 FALSE이며 Need[i] <= Work[i]임을 동시에 만족
				for (int j = 0; j < m; j++)
					Work[j] = Work[j] + (Pr + i)->ALLOCATION[j];		// Work[j] = Work[i] + ALLOCATION[i]
				Finish[i] = true;
				Q.push((Pr + i)->Pnum);									// safety된 순서대로 큐에 저장
			}

			else{														// 조건이 만족되지 않으면 Safety인지 UnSafety인지 확인
				if (SafetyCheck(Finish))
					flag = true;
				else
					flag = false;
			}
		}
	}

	if (flag){
		printf("result : safe --> ");
		PrintQ(Q);
		printf("\n");
	}

	else{
		printf("result : Unsafe --> ");

		for (int i = 0; i < n; i++)
			if (Finish[i] == false)
				printf("P[%d] ", (Pr + i)->Pnum);
		printf("\n");
	}
}

void FindNum(char *filename){
	int i = 0;
	char line[MAX_LINE], *tok;
	FILE *fp;
	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }

	while (fgets(line, MAX_LINE, fp)){
		tok = strtok(line, DELIM);

		do{
			switch (i){
			case 0:
				m = atoi(tok);
				break;

			case 1:
				n = atoi(tok);
				break;
			}
			i++;

			if (i == 2) 	break;

		} while (tok = strtok(NULL, DELIM));
	}
	fclose(fp);
}

void ReadFile(char *filename, Process *P, int *Available){
	int LineCount = 0 , Resource_num = 0 , Process_num = 0;
	char line[MAX_LINE], *tok;
	FILE *fp;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }
	
	while (fgets(line, MAX_LINE, fp)){
		printf("%s", line);
		tok = strtok(line, DELIM);

		do{
			if (2 < LineCount && LineCount < 3 + n){
				if (Resource_num == 0)
					(P + Process_num)->Pnum = Process_num;
				else
					(P + Process_num)->ALLOCATION[Resource_num - 1] = atoi(tok);
				Resource_num++;
			}

			else if (4 + n < LineCount && LineCount < 5 + (2 * n)){
				if (Resource_num == 0)
					(P + Process_num)->Pnum = Process_num;
				else
					(P + Process_num)->MAX[Resource_num - 1] = atoi(tok);
				Resource_num++;
			}

			else if (6 + (2 * n) < LineCount){
				*(Available + Resource_num) = atoi(tok);
				Resource_num++;
			}

		} while (tok = strtok(NULL, DELIM));
		
		if ((2 < LineCount && LineCount < 3 + n) || (4 + n < LineCount && LineCount < 5 + (2 * n)))
			Process_num++;
		else
			Process_num = 0;

		Resource_num = 0;
		LineCount++;
	}
	fclose(fp);
}

Process *InitProcess(){
	Process *P;
	P = (Process*)malloc(sizeof(Process)*n);

	for (int i = 0; i < n; i++){
		(P + i)->ALLOCATION = (int*)malloc(sizeof(int)*m);
		(P + i)->MAX = (int*)malloc(sizeof(int)*m);
		(P + i)->NEED = (int*)malloc(sizeof(int)*m);

		for (int j = 0; j < m; j++){
			(P + i)->ALLOCATION[j] = NULL;
			(P + i)->MAX[j] = NULL;
			(P + i)->NEED[j] = NULL;
		}
	}
	return P;
}


int *InitAvailable(){
	int *Available = (int*)malloc(sizeof(int)*m);

	for (int j = 0; j < m; j++)
		*(Available + j) = NULL;

	return Available;
}

bool *InintFinish(){
	bool *Finish = (bool*)malloc(sizeof(bool)* n);

	for (int i = 0; i < n; i++)
		*(Finish + i) = false;

	return Finish;
}

void GetNeed(Process *P){
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			(P + i)->NEED[j] = (P + i)->MAX[j] - (P + i)->ALLOCATION[j];
}

bool SafetyCheck(bool *Finish){
	for (int i = 0; i < n; i++){
		if (Finish[i] != true)
			return false;
	}
	return true;
}

bool Need_WorkCheck(Process P, int *Work){
	for (int i = 0; i < m; i++){
		if (P.NEED[i] > Work[i])
			return false;
	}
	return true;
}

void PrintQ(queue<int> Q){
	while (!Q.empty()){
		printf("P[%d] ",Q.front());
		Q.pop();
	}
}