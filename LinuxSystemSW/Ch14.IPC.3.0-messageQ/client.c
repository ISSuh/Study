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


#include <sys/msg.h>



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

#include <sys/msg.h>
#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

//#############################################################################
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("USAGE: ] ./client [string] \n");
		exit(0);
	}


    int res, i;
    struct my_msg_st some_data;
    int msgid;

	memset(&some_data, '\0', sizeof(some_data));
	strcpy(some_data.some_text, argv[1]);

	msgid = msgget((key_t)2011270314, 0666 | IPC_CREAT);
	some_data.my_msg_type = 5;
	
	res = msgsnd(msgid,(void*)&some_data, MAX_TEXT, 0);
	if(res == -1) exit(EXIT_FAILURE);

	printf("\n");
	printf("Client In  --> [%s]\n", some_data.some_text);

	usleep(1000);

	res = msgrcv(msgid,(void *)&some_data,MAX_TEXT,6,0);
	if(res == -1) exit(EXIT_FAILURE);
	
	printf("Client Out --> [%s]\n", some_data.some_text);


	if (msgctl(msgid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Client Process %d finished\n", getpid());
	printf("Client Execution finished successfully.... \n\n\n");
    exit(EXIT_SUCCESS);

}
