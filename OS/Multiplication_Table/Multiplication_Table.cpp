#include <stdio.h>

int main(){
	int i, j, k, num;

	printf("Hello World!!\n");
	printf("max multiflication number = ");
	scanf_s("%d", &num);

	for (k = 1; k <= num; k = k + 5){ // ������ ù������ 1,6,11...�̹Ƿ� k+5���Ͽ� �ݺ����� �����Ѵ�.

		for (i = 1; i <= num; i++){ // i�� ���� ���� ������ ����ؾ��ϹǷ� �Է°���ŭ �ݺ��� �Ѵ�.

			for (j = k; j <= k+4; j++){ // �Ѷ��ο� �ִ� 5���� ������ ǥ���ϱ����� k+4�� ������ �ɾ�д�.

				if (j > num){ // 5���� ������ ����ؾ� �ϹǷ� j�� �Է°����� Ŀ���� �ݺ����� Ż���ϵ��� �Ѵ�.
					printf("\n");
					continue;
				}

				else if (j < i){ // ���� �������� ���������� �����ؾ� �ϹǷ�, j�� i���� ����������� ����ϰ� �ݺ����� Ż���Ѵ�. 
					printf("		");
					continue;
				}

				printf(" %d X %d = %d	", j,i, i*j); // ������ ����Ʈ�Ѵ�.

			}
		}
	}
	return 0;
}