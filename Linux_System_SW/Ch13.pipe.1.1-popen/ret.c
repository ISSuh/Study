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
// Due    : Dec. 01, 2015 21:00
//#############################################################################


//#############################################################################
// Complete a program which executes the following shell commands.
// ] ls -l | wc
// 1. Implement it by using two popen() pipe functions.
// 2. execute each command by using seperate popen(). 
//		a popen() for 'ls' command, the other popen() for 'wc' command.


//#############################################################################
int main(int argc, char **argv)
{

   	int res, i;
	if (argc != 1)
	{
		printf("USAGE: ] ./ret \n");
		exit(EXIT_FAILURE);
	}

	FILE *r_fp,*w_fp;
	char buffer[BUFSIZ + 1];
	int chars_read;

	memset(buffer,'\0',sizeof(buffer));

	r_fp = popen("ls -l","r");
	if(r_fp != NULL){
		chars_read = fread(buffer,sizeof(char),BUFSIZ,r_fp);
		pclose(r_fp);
	}	

	w_fp = popen("wc","w");
	if(w_fp != NULL){
		chars_read = fread(buffer,sizeof(char),BUFSIZ,w_fp);
		fwrite(buffer,sizeof(char),strlen(buffer),w_fp);

		if(chars_read > 0 )
			printf("%s",buffer);

		pclose(w_fp);
	}
	

	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);

}

