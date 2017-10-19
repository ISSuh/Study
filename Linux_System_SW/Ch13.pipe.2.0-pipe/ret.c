#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>





//#############################################################################
// Request: Complete the following functions. 
// Due    : Dec. 2, 2015 21:00
//#############################################################################


// Implement the following shell command using pipe() functions
// ] ls -l | wc -lmc 




//#############################################################################
int main(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("USAGE: ] ./ret \n");
		exit(EXIT_FAILURE);
	}

	int data_processed;
    int file_pipes[2];
    pid_t fork_result;

    if (pipe(file_pipes) != 0) 
		exit(EXIT_SUCCESS);
       
	fork_result = fork(); // �ڽ� ���μ��� ����

    if (fork_result == (pid_t)-1) {
		fprintf(stderr, "Fork failure");
        exit(EXIT_FAILURE);
		}

    if (fork_result == (pid_t)0) { // �ڽ� ���μ���
		 close(0); // std in �ݱ�
         dup(file_pipes[0]); // ���� ��ũ���� 0�� ���ο� read (file_pipes[0])�Ҵ�
         close(file_pipes[0]); // ������ �ִ� ������ ���ϼ����� read �ݱ�
         close(file_pipes[1]); // ������ �ִ� ������ ���ϼ����� write �ݱ�

         execlp("wc", "wc", "-lmc",0); // ���μ��� wc -lmc ���� ���� �ڵ�� ���� X
         exit(EXIT_FAILURE);
        }
       
	else { // �θ� ���μ���
		close(1); // std out �ݱ�
		dup(file_pipes[1]); // ���� ��ũ���� 1�� ���ο� write (file_pipes[1]) �Ҵ�
		close(file_pipes[0]); // ������ �ִ� ������ ���� ������ read �ݱ�
		close(file_pipes[1]); // ������ �ִ� ������ ���� ������ write �ݱ�

		execlp("ls", "ls", "-l",0); // ���μ��� ls -l ���� ���� �ڵ�� ���� X
		//execlp("cat", "cat", "ret.c",0); // wc -lmc < ret.c
		exit(EXIT_FAILURE);
		}
		// wait�� ����Ͽ� �θ� ������ ���� ���ϵ� ���μ����� ������ �Ѵ�. �׷��� �Ϸ��� �� ���α׷��� ���
		// �ΰ��� ���μ����� �����ؾ��Ѵ�. execlp()�� ����ϸ� ���� wait�� ������ �����Ƿ� 
    

	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);

}
