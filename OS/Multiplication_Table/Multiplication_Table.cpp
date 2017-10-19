#include <stdio.h>

int main(){
	int i, j, k, num;

	printf("Hello World!!\n");
	printf("max multiflication number = ");
	scanf_s("%d", &num);

	for (k = 1; k <= num; k = k + 5){ // 곱셈의 첫시작은 1,6,11...이므로 k+5를하여 반복문을 실행한다.

		for (i = 1; i <= num; i++){ // i는 같은 수의 곱까지 출력해야하므로 입력값만큼 반복을 한다.

			for (j = k; j <= k+4; j++){ // 한라인에 최대 5개의 곱셈을 표현하기위해 k+4의 조건을 걸어둔다.

				if (j > num){ // 5개씩 곱셈을 출력해야 하므로 j가 입력값보다 커지면 반복문을 탈출하도록 한다.
					printf("\n");
					continue;
				}

				else if (j < i){ // 같은 수끼리의 곱셈까지만 연산해야 하므로, j가 i보다 작으면공백을 출력하고 반복문을 탈출한다. 
					printf("		");
					continue;
				}

				printf(" %d X %d = %d	", j,i, i*j); // 곱셈을 프린트한다.

			}
		}
	}
	return 0;
}