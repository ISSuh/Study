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



//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 25, 2015 21:00
//#############################################################################



// Make the function  print_int_list() to be executed one at a time by mutiple threads.
// Multiple execution of this function should not be interleaved.
// An example output should be like below:
//
//thread  3 = [  0  1  2  3]
//thread  1 = [  0  1  2  3  4  5  6]
//thread  2 = [  0  1  2  3  4  5  6  7  8  9]
//thread  4 = [  0  1  2  3  4  5  6  7]
//thread  0 = [  0  1  2  3  4  5]
//thread  3 = [  0  1  2  3]
//thread  1 = [  0  1  2  3  4  5  6]
//thread  2 = [  0  1  2  3  4  5  6  7  8  9]
//thread  4 = [  0  1  2  3  4  5  6  7]
//thread  0 = [  0  1  2  3  4  5]
//thread  3 = [  0  1  2  3]
//thread  1 = [  0  1  2  3  4  5  6]
//thread  2 = [  0  1  2  3  4  5  6  7  8  9]
//thread  4 = [  0  1  2  3  4  5  6  7]
//thread  0 = [  0  1  2  3  4  5]


sem_t sem;
//pthread_mutex_t mut;

//#############################################################################
void print_int_list(int id, int max_num) 
{
	printf("thread %2d = [", id); fflush(stdout);
	
	for(int i=0; i<=max_num; i++)
	{
		printf("%3d", i); fflush(stdout);
		usleep(100000);
	}
	printf("]\n");
}



#define MAX_LOOP	3
//#############################################################################
void *thread_function(void *arg) 
{
	int id = *(int*)arg;
	int max_num = rand() % 10 + 1;	

	sem_post(&sem);

	for(int i=0; i<MAX_LOOP; i++)
	{
		usleep(100000);
		//pthread_mutex_lock(&mut);
		sem_wait(&sem);
		print_int_list(id, max_num);
		//pthread_mutex_unlock(&mut);
		sem_post(&sem);
	}
    pthread_exit(NULL);
}



#define MAX_THREAD 5

//#############################################################################
int main(int argc, char **argv)
{

	if (argc != 1)
	{
		printf("USAGE: ] ./ret\n");
		exit(0);
	}

	srand( time(NULL) );


	int res, i;
    pthread_t thread_id[MAX_THREAD];
	int thread_arg[MAX_THREAD];
	
	//res = pthread_mutex_init(&mut,NULL);
	res = sem_init(&sem,0,1);
	
	for( i=0; i<MAX_THREAD; i++)
	{
		thread_arg[i] = i;
		//printf("arg = %2d\n", thread_arg[i]);
		res = pthread_create(&thread_id[i], NULL, thread_function, (void *)&thread_arg[i]);
		sem_wait(&sem);
	}


	for( i=0; i<MAX_THREAD; i++)
	{
		res = pthread_join(thread_id[i], NULL);
		//printf("Thread %d finished ...\n", i);
	}

	//pthread_mutex_destroy(&mut);
	sem_destroy(&sem);

	printf("Execution finished successfully.... \n\n");

}
