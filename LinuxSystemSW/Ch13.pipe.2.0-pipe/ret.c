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
       
	fork_result = fork(); // 자식 프로세스 생성

    if (fork_result == (pid_t)-1) {
		fprintf(stderr, "Fork failure");
        exit(EXIT_FAILURE);
		}

    if (fork_result == (pid_t)0) { // 자식 프로세스
		 close(0); // std in 닫기
         dup(file_pipes[0]); // 파일 디스크립터 0에 새로운 read (file_pipes[0])할당
         close(file_pipes[0]); // 기존에 있던 파이프 파일서술자 read 닫기
         close(file_pipes[1]); // 기존에 있던 파이프 파일서술자 write 닫기

         execlp("wc", "wc", "-lmc",0); // 프로세스 wc -lmc 실행 이후 코드는 실행 X
         exit(EXIT_FAILURE);
        }
       
	else { // 부모 프로세스
		close(1); // std out 닫기
		dup(file_pipes[1]); // 파일 디스크립터 1에 새로운 write (file_pipes[1]) 할당
		close(file_pipes[0]); // 기존에 있던 파이프 파일 서술자 read 닫기
		close(file_pipes[1]); // 기존에 있던 파이프 파일 서술자 write 닫기

		execlp("ls", "ls", "-l",0); // 프로세스 ls -l 실행 이후 코드는 실행 X
		//execlp("cat", "cat", "ret.c",0); // wc -lmc < ret.c
		exit(EXIT_FAILURE);
		}
		// wait를 사용하여 부모가 끝나기 전에 차일드 프로세스가 끝나야 한다. 그렇게 하려면 이 프로그램의 경우
		// 두개의 프로세스를 생성해야한다. execlp()를 사용하면 이후 wait를 읽을수 없으므로 
    

	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);

}
