#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>



//#############################################################################
// Request: Complete the following program. 
// Due    : 2015-10-06 24:00
//#############################################################################


// Implement the following shell command using directory system calls 
// ] mkdir a/b/c/d/e/f/g/h/i/j/k/l/m/n -p
//
//
// ] ls -R a
// ] tree a

// good luck!

	
//#############################################################################

int main(int argc, char **argv)
{
	char path[] = "a/b/c/d/e/f/g/h/i/j/k/l/m/n";
	int i;
	char *c;
	
	c = strtok(path,"/");
	
	while(c != NULL){
		mkdir(c,0777);
		chdir(c);
		c = strtok(NULL,"/");
	}
	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);
}
