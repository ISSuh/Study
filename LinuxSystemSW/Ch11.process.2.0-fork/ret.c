#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>



//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 04, 2015 24:00
//#############################################################################



//#############################################################################
// Complete this function which executes "find" command simultaneously.
// 
// For example, when you execute this program with the command line "]./ret /etc httpd* *xml web*"
// This program executes three "find" programs simultaneously
//	] find /etc -name httpd* &
//	] find /etc -name *xml &
//  ] find /etc -name web* &
//  
// You should use fork() and exec() system calls to create child processes.
// 
// On completion of the multiple concurrent execution of the find command,
// This program print out the PIDs and Exitcodes of child processes.
//
int main(int argc, char **argv)
{
	int i,pid,num_child = argc - 2,stat_val;

	if (argc < 2)
	{
		printf("USAGE  : ] ./ret [dir_path] [search pattern list]\n");
		printf("Example: ] ./ret /home  ret.c Makefile ");
		printf("Example: ] ./ret /etc  httpd* *xml web* ");

		exit(0);
	}

	for(i=2; i<argc; i++)
		printf("search word %2d = [%s]\n", i, argv[i]);
	printf("num_child = %d\n",num_child);
	printf("\n");
	getchar();	

	//close(2);

	for(i =2 ; i<argc; i++){
		pid = fork();
		switch(pid){
		case -1:
			printf("fork failed");
			break;
		case 0:
			//printf("Child[%d] : <<%s>>\n",i,argv[i]);
			execl("/bin/find","find",argv[1],"-name",argv[i],0);
			//exit(i);
			break;
		default:
			//printf("Parent\n");
			break;
		}
	}

	sleep(1);
	printf("\nAll child processes finished successfully.... \n\n");

	for(i = 2 ; i<argc ; i++){
		if(pid != 0){
			printf("Child PID : %d\n",wait(&stat_val));
			if(WIFEXITED(stat_val))
				printf("Child Exit Code : %d\n",WEXITSTATUS(stat_val));
			else 
				printf("Child terminated abnormally\n");
		}
	}
	/*
	for(i = 2 ; i<argc ; i++){
		listpid[i] = wait(&stat_val);
		if(WIFEXITED(stat_val)) listexit[i] = WEXITSTATUS(stat_val);
	*/

	/*for(i = 2; i<argc ; i++)
		printf("Child PID: %d, Child Exit Code : %d",listpid[i],listexit[i]);
	*/
	return 1;
}
