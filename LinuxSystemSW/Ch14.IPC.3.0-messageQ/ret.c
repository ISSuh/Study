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
// Due    : Dec. 9, 2015 21:00
//#############################################################################


//#############################################################################
// Complete this client program which acts as follows
// - read a string from the 1st argument of the program
// - print the string on the screen
// - send the string to the server through a MESSAGE QUEUE
// - receive a string from the server through the MESSAGE QUEUE
// - print the received string on the screen.
//
// - we assume that the server is always executed before the client .



/*

step 1. [client] ---> "abc" ---> [server]
step 2. [client] <--- "ABC" <--- [server]

using MESSAGE QUEUE
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


	// execut server
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

	// execut client
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

	

	int status;
	wait(&status);
	wait(&status);

	printf("\n\n");
	printf("Execution finished successfully.... ./ret\n\n");
    exit(EXIT_SUCCESS);

}
