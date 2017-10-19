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
};												// ����� ǥ���ϴ� ����ü ����� ���ҿ� row, colum
struct thrdMat{
	Mat A,B;
	int Arow, Bcol, Acol, result;
};												// ��İ��� �ϱ����� �����带 �����Ҷ�, ���ڷ� �Ѱ��ֱ� ���� ����ü

void read_matrix(Mat &matrix, char *filename);  // ������ ����� �а� ���ڷ� ��ȯ�ϱ����� ���� ���̵��� 'read_matrix'�Լ� �̿�
void SaveMatrix(Mat matrix, char * fileName);   // ������� ���Ϸ� ���
void Multi(Mat x, Mat y, Mat *out);			    // ��İ� �Լ�
void InitMatrix(Mat *matrix);					// ����� ���Ҹ� �ʱ�ȭ
void PrintMatrix(Mat matrix);					// ����� ����Ʈ�ϴ� �Լ�
void PrintCal(Mat A, Mat B, Mat C);				// ��� ������ ����Ʈ�ϴ� �Լ�
DWORD WINAPI ThreadFunction(LPVOID Param);		// ������ ������ ����Ǵ� �Լ�

int main(int argc, char** argv){
	
	if (argc < 2){ printf("Error: Lack Param\n"); exit(0);	}
	else if (argc > 11){ printf("Error: Many Param.\n"); exit(0);}		// ����� ���ڰ� 2������ ���ų�, 10������ ���ٸ� ����
	printf("\n");

	int start = 0, end = 0;						// �ð��� �����ϱ� ���� ����
	Mat *matrix = (Mat*)malloc(sizeof(Mat)* (argc - 1));		// ��������� ���� -1 ��ŭ ����ü�� ����
	Mat *temp = (Mat*)malloc(sizeof(Mat) * (argc - 2));		// ��� ���� ���� ����ü�� ������ ���� -2 ��ŭ ����
	
	start = GetTickCount();						// ����� �����ϱ����� ������ ����

	for (int i = 1; i < argc; i++)				// ������ ����� �����ϰ� �̸� matrix����ü�� ��ġȭ�Ͽ� ����
		read_matrix(*(matrix+i-1), argv[i]);

	Multi(matrix[0],matrix[1],temp+0);			// ó���� �ι�° ����� ���� ����
	PrintCal(matrix[0], matrix[1], temp[0]);
	
	if (argc > 3){								// ������ ������ 2������ ���ٸ� ó�� ���� ��İ��� ���� ������ ���ʴ�� ����
		for (int i = 0; i < argc - 3; i++){
			Multi(temp[i], matrix[i + 2], temp + (i + 1));
			PrintCal(temp[i], matrix[i + 2], temp[i+1]);
		}
	}

	end = GetTickCount();						// ����� �������� �ð��� ����

	PrintMatrix(*(temp + (argc - 3)));			// temp�迭�� �������� ��İ��� ������ �̹Ƿ� temp�迭�� ������ ����� ���
	printf("\nProcessing Time: %5.3fsec\n\n", (end - start) / 1000.0);	// ó���� ������ �ð��� ���� ����ϴ� �ð��� ����

	SaveMatrix(*(temp + (argc - 3)), "result.txt");			// �ϼ��� ����� ���Ϸ� ���	

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

	int k = 0;									// �������� id�� ������ ����
	thrdMat tmp;								// ����������� �Ѱ��� ����
	HANDLE *hThread = (HANDLE*)malloc(sizeof(HANDLE)* (x.Mr*y.Mc));		// �������ڵ��� ������ ������ ������ŭ ����
	DWORD *thrdId = (DWORD*)malloc(sizeof(DWORD) * (x.Mr*y.Mc));		// ��������̵� ������ ������ ������ŭ ����
	
	InitMatrix(out);
	tmp.Acol = x.Mc;
	tmp.A = x; tmp.B = y;
	out->Mr = x.Mr; out->Mc = y.Mc;				// ��İ��� �ϱ�����, �ʱ�ȭ�� ��� ���� �������� ����

	for (int i = 0; i < x.Mr; i++){				// ��İ�
		for (int j = 0; j < y.Mc; j++){
			tmp.Arow = i; tmp.Bcol = j;	

			*(hThread + k) = CreateThread(NULL, 0, ThreadFunction, &tmp, 0, thrdId + k);	// �����带 ����Ͽ� ��İ��� ���Ҹ� ����
			WaitForSingleObject(*(hThread + k), INFINITE);				// ������ �����尡 ����Ǳ⸦ ��ٸ�

			out->M[i][j] = tmp.result;			// ����� ����
			k++;								 
		}
	}

	Sleep(1000);								// 1�ʰ� ���

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
	thrdMat *matrix = (thrdMat*)Param;			// ������ ������ �Ѱܹ��� ������ ����
	matrix->result = 0;

	for (int i = 0; i < matrix->Acol; i++)		// ����� ���Ҹ� ���
		matrix->result += matrix->A.M[matrix->Arow][i] * matrix->B.M[i][matrix->Bcol];

	return 0;
}