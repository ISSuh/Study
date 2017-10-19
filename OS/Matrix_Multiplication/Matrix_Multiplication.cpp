#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable:4996)

#define MAX_ROW		100
#define MAX_COL		100
#define DELIM		" \r\t"
#define MAX_LINE	1000

struct Mat{
	int M[MAX_ROW][MAX_COL];
	int Mr, Mc;
};												// 행렬을 표현하는 구조체 행렬의 원소와 row, colum
struct thrdMat{
	Mat A,B;
	int Arow, Bcol, Acol, result;
};												// 행렬곱을 하기위해 스레드를 생성할때, 인자로 넘겨주기 위한 구조체

void read_matrix(Mat &matrix, char *filename);  // 파일의 행렬을 읽고 숫자로 변환하기위해 과제 가이드중 'read_matrix'함수 이용
void SaveMatrix(Mat matrix, char * fileName);   // 결과물을 파일로 출력
void Multi(Mat x, Mat y, Mat *out);			    // 행렬곱 함수
void InitMatrix(Mat *matrix);					// 행렬의 원소를 초기화
void PrintMatrix(Mat matrix);					// 행렬을 프린트하는 함수
void PrintCal(Mat A, Mat B, Mat C);				// 계산 과정을 프린트하는 함수
DWORD WINAPI ThreadFunction(LPVOID Param);		// 스레드 생성시 실행되는 함수

int main(int argc, char** argv){
	
	if (argc < 2){ printf("Error: Lack Param\n"); exit(0);	}
	else if (argc > 11){ printf("Error: Many Param.\n"); exit(0);}		// 실행시 인자가 2개보다 적거나, 10개보다 많다면 오류
	printf("\n");

	int start = 0, end = 0;						// 시간을 측정하기 위한 변수
	Mat *matrix = (Mat*)malloc(sizeof(Mat)* (argc - 1));		// 행렬파일의 갯수 -1 만큼 구조체를 생성
	Mat *temp = (Mat*)malloc(sizeof(Mat) * (argc - 2));		// 행렬 곱에 사용될 구조체를 파일의 갯수 -2 만큼 생성
	
	start = GetTickCount();						// 계산을 시작하기전에 시작을 측정

	for (int i = 1; i < argc; i++)				// 파일의 행렬을 조사하고 이를 matrix구조체에 수치화하여 저장
		read_matrix(*(matrix+i-1), argv[i]);

	Multi(matrix[0],matrix[1],temp+0);			// 처음과 두번째 행렬을 먼저 곱함
	PrintCal(matrix[0], matrix[1], temp[0]);
	
	if (argc > 3){								// 파일의 갯수가 2개보다 많다면 처음 구한 행렬곱에 다음 파일을 차례대로 곱함
		for (int i = 0; i < argc - 3; i++){
			Multi(temp[i], matrix[i + 2], temp + (i + 1));
			PrintCal(temp[i], matrix[i + 2], temp[i+1]);
		}
	}

	end = GetTickCount();						// 계산이 끝난후의 시간을 측정

	PrintMatrix(*(temp + (argc - 3)));			// temp배열의 마지막이 행렬곱의 마지막 이므로 temp배열의 마지막 행렬을 출력
	printf("\nProcessing Time: %5.3fsec\n\n", (end - start) / 1000.0);	// 처음과 마지막 시간을 빼서 계산하는 시간을 구함

	SaveMatrix(*(temp + (argc - 3)), "result.txt");			// 완성된 행렬을 파일로 출력	

	free(matrix);	
	free(temp);
}

void read_matrix(Mat &matrix, char *filename)
{
	char line[MAX_LINE], *tok;
	FILE *fp;

	if (!(fp = fopen(filename, "r"))) { printf("ERROR: file open\n"); exit(0); }
	matrix.Mr = 0;
	while (fgets(line, MAX_LINE, fp)){
		tok = strtok(line, DELIM);
		matrix.Mc = 0;
		do
		{
			matrix.M[matrix.Mr][matrix.Mc++] = atoi(tok);

		} while (tok = strtok(NULL, DELIM));
		matrix.Mr++;
	}
	fclose(fp);
}

void SaveMatrix(Mat matrix, char * fileName){
	FILE * fp = NULL;

	if (!(fp = fopen(fileName, "w+"))){ printf("Error: File Write\n"); exit(0); }

	for (int i = 0; i < matrix.Mr; i++){
		for (int j = 0; j < matrix.Mc; j++){
			fprintf(fp, "%10d", matrix.M[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

void Multi(Mat x, Mat y, Mat *out){

	int k = 0;									// 스레드의 id를 저장할 변수
	thrdMat tmp;								// 스레드생성시 넘겨줄 변수
	HANDLE *hThread = (HANDLE*)malloc(sizeof(HANDLE)* (x.Mr*y.Mc));		// 쓰레드핸들을 생성할 쓰래드 갯수만큼 생성
	DWORD *thrdId = (DWORD*)malloc(sizeof(DWORD) * (x.Mr*y.Mc));		// 쓰레드아이디를 생성할 쓰래드 갯수만큼 생성
	
	InitMatrix(out);
	tmp.Acol = x.Mc;
	tmp.A = x; tmp.B = y;
	out->Mr = x.Mr; out->Mc = y.Mc;				// 행렬곱을 하기위해, 초기화및 행과 열의 갯수등을 저장

	for (int i = 0; i < x.Mr; i++){				// 행렬곱
		for (int j = 0; j < y.Mc; j++){
			tmp.Arow = i; tmp.Bcol = j;	

			*(hThread + k) = CreateThread(NULL, 0, ThreadFunction, &tmp, 0, thrdId + k);	// 쓰레드를 사용하여 행렬곱의 원소를 구함
			WaitForSingleObject(*(hThread + k), INFINITE);				// 생성된 쓰레드가 종료되기를 기다림

			out->M[i][j] = tmp.result;			// 결과를 저장
			k++;								 
		}
	}

	Sleep(1000);								// 1초간 대기

	free(hThread);
	free(thrdId);
}

void InitMatrix(Mat *matrix){
	for (int i = 0; i < matrix->Mr; i++){
		for (int j = 0; j < matrix->Mc; j++){
			matrix->M[i][j] = 0;
		}
	}
}
		
void PrintMatrix(Mat matrix){
	printf("\n");

	for (int i = 0; i < matrix.Mr; i++){
		for (int j = 0; j < matrix.Mc; j++){
			printf("%10d", matrix.M[i][j]);
		}
		printf("\n");
	}
}

void PrintCal(Mat A, Mat B, Mat C){
	printf("( %3d x %3d ) X ( %3d x %3d ) = ( %3d x %3d )\n", A.Mr, A.Mc, B.Mr, B.Mc, C.Mr, C.Mc);
}

DWORD WINAPI ThreadFunction(LPVOID Param){
	thrdMat *matrix = (thrdMat*)Param;			// 스래드 생성시 넘겨받은 변수를 저장
	matrix->result = 0;

	for (int i = 0; i < matrix->Acol; i++)		// 행렬의 원소를 계산
		matrix->result += matrix->A.M[matrix->Arow][i] * matrix->B.M[i][matrix->Bcol];

	return 0;
}