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
#include <sys/types.h>
#include <sys/wait.h>






//#############################################################################
// Request: Complete the following functions. 
// Due    : Dec. 03, 2013 21:00
//#############################################################################


//#############################################################################
// Complete this server program which acts as follows
// - receive a string from a client through a named pipe [./my_fifo] 
// - print the string on the screen
// - convert the string to UPPER case.
// - print the result string on the screen.
// - send the result string to the client through a named pipe [./my_fifo]


/*

step 1. [client] ---> "abc" ---> [server]
step 2. [client] <--- "ABC" <--- [server]

*/

//#############################################################################
int main(int argc, char **argv)
{

   	int res, i;
	if (argc != 2)
	{
		printf("USAGE: ] ./ret [string] \n");
		exit(EXIT_FAILURE);
	}


    pid_t fork_result;


	// execute server
	fork_result = fork();
	if (fork_result == (pid_t)-1) 
	{
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}

	if (fork_result == (pid_t)0) 
	{
		execl("./server", "server", (char *)0);
		exit(EXIT_FAILURE);
	}

	usleep(100000);		// 100 msec of sleep

	// execute client
	fork_result = fork();
	if (fork_result == (pid_t)-1) 
	{
		fprintf(stderr, "Fork failure");
		exit(EXIT_FAILURE);
	}

	if (fork_result == (pid_t)0) 
	{
		execl("./client", "client", argv[1], (char *)0);
		exit(EXIT_FAILURE);
	}

	
	
	// wait for the processes to finish
	int status;
	wait(&status);
	wait(&status);

	printf("\n\n");
	printf("Execution finished successfully.... ./ret\n\n");
    exit(EXIT_SUCCESS);

}
