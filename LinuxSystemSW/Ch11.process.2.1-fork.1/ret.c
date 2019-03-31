#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 10, 2015 18:00
//#############################################################################



//#############################################################################
// Complete this code which 
// 1. executes multiple "mysleep" programs simultaneously and
// 2. print out the following on the screen.
 
//	mysleep:   10000000 1 1s
//	mysleep:    1000000 2 0.1s
//	mysleep:     100000 3 0.01s
//	mysleep:      10000 4 0.001s
//	mysleep:       1000 5
//	mysleep:       1000 5
//	mysleep:      10000 4
//	mysleep:     100000 3
//	mysleep:    1000000 2
//	mysleep:   10000000 1
//	mysleep:    1000000 6
//	mysleep:     100000 7 
//	mysleep:      10000 8
//	mysleep:       1000 9
//	mysleep:       1000 9
//	mysleep:      10000 8
//	mysleep:     100000 7
//	mysleep:    1000000 6

// You should use fork(), exec(), and wait()/waitpid() system calls to create child processes.
// 
//
int main(int argc, char **argv)
{
	int i,j,pid,stat_val,str_int = 100000000;
	char str_char[20] = {0};
	
	if (argc != 1)
	{
		printf("USAGE  : ] ./ret \n");
		exit(0);
	}
	
	for(j = 0 ; j < 2 ; j++){
		for(i = 0 ; i< 5-j ; i++){
			pid = fork();
		
			str_int = str_int/10;
			sprintf(str_char,"%d",str_int);

			usleep(1000);

			switch(pid){
			case -1:
				printf("fork failed");
				break;
			case 0:
				execl("./mysleep", "mysleep", str_char, 0);
				break;
			default:
				break;
			}
		}
		
		for(i = 0 ; i<5-j; i++)
			wait(&stat_val);
		
		str_int = 10000000;
	}

	/*for(i = 0 ; i<5; i++)
		wait(&stat_val);

	str_int = 10000000;

	for(i = 0 ; i< 4; i++){
		pid = fork();
		
		str_int = str_int/10;
		sprintf(str_char,"%d",str_int);

		usleep(1000);

		switch(pid){
		case -1:
			printf("fork failed");
			break;
		case 0:
			execl("./mysleep", "mysleep", str_char, 0);
			break;
		default:
			break;
		}
		
	}
	

	for(i = 0 ; i<4	; i++)
		wait(&stat_val);*/

	printf("All child processes finished successfully.... \n\n");
	return 1;
}
