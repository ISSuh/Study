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




//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 17, 2015 21:00
//#############################################################################



// 1. create 5 threads 
// 2. set a unique value(unsigned integer from 0 to 4) to each thread 
// 3. each thread prints out its value on the screen three times
// 4. the output on the screen should be as follows.

/*
	thread 0
	thread 1
	thread 2
	thread 3
	thread 4
	thread 0
	thread 1
	thread 2
	thread 3
	thread 4
	thread 0
	thread 1
	thread 2
	thread 3
	thread 4
	Execution finished successfully.... 
*/

#define MAX_THREAD	5

void *func(void *arg){
	int i;
	for(i = 0 ; i<3 ;i++){
		printf("Thread[%d]\n",(int *)arg);
		sleep(1);
	}
}
/*
int run_now = 0;
void *func2(void *arg){
	int num = (int arg);
	int i;
	i =0
	while(i<3){
		if(run_now == num){
			printf("Thread %d\n",num);
			if(num==4) printf("\n");
				i++;
				run_now = (run_now + 1) % MAX_THREAD;
			}
		else usleep(100);
	}
}
*/

//#############################################################################
int main(int argc, char **argv)
{

    int res, i,j;
	void *num;
    pthread_t a_thread[MAX_THREAD];
	int arg[MAX_THREAD];

	if (argc != 1)
	{
		printf("USAGE: ] ./ret \n");
		exit(0);
	}

	for(i = 0 ; i<MAX_THREAD ; i++){
		res = pthread_create(&a_thread[i],NULL,func,(void*)i);
		usleep(1000);
	}
	for(i= 0 ; i<MAX_THREAD ;i++)
		res = pthread_join(a_thread[i],&num);
	

	printf("Execution finished successfully.... \n\n");
}
