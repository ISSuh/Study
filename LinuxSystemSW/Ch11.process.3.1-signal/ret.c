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



//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 11, 2015 21:00
//#############################################################################



//#############################################################################
// Complete the program which terminates its execution after various expiration time from the starting time.
// The expiration time is given to the program as an argument in seconds.
// You should use signal SIGINT only.

int g_i=0;


void Quit(int sig){
	g_i = -1;
}

//#############################################################################
int main(int argc, char **argv)
{
	int pid,num = atoi(argv[1]);

	if (argc != 2)
	{
		printf("USAGE: ] ./ret  <seconds>\n");
		exit(0);
	}


	struct timeval tv1, tv2; // check time of system
	gettimeofday( &tv1, NULL);
	printf("\ntime = %10d.%03d\n\n", tv1.tv_sec, tv1.tv_usec/1000);
	//sleep(5);	

	pid = fork();
	switch(pid){
		case -1:
			perror("fork failed");
			exit;
		case 0:
			sleep(num);
			kill(getppid(),SIGINT);
			exit(0);
	}

	(void)signal(SIGINT,Quit);


	for(g_i=1; g_i ; g_i++)
	{
		printf("%3d ", g_i); fflush(stdout);	
		if( g_i % 20 == 0 ) printf("\n");
		usleep(100000);		// 0.1 second sleep
	}


	// ... print out the ending time
	gettimeofday( &tv2, NULL);
	printf("\n\ntime = %10d.%03d\n\n", tv2.tv_sec, tv2.tv_usec/1000);

	if( tv2.tv_usec >= tv1.tv_usec)
		printf("Execution Time: %10d:%03d\n\n", tv2.tv_sec - tv1.tv_sec, (tv2.tv_usec - tv2.tv_usec)/1000 );
	else
		printf("Execution Time: %10d:%03d\n\n", tv2.tv_sec - tv1.tv_sec - 1, (1000000 + tv2.tv_usec - tv2.tv_usec)/1000 );

}
