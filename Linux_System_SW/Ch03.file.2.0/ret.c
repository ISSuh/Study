#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>



//#############################################################################
// Request: Complete the following program. 
// Due    : 2014-15-03 18:00
//#############################################################################


// Complete the program which converts all lower-case letters to upper-case in the file [infile].

// You should use the low-level I/O functions to manuplate the file [infile]
// Your program should not create any new file during its excution.
// input file:  infile
// output file: infile
//
// good luck!



//#############################################################################
int main(int argc, char **argv)
{
	char c;
	int in,adr;

	in = open("infile", O_RDWR);
	while(read(in,&c,1) == 1){

		if(c >= 'a' && c <= 'z'){
			c = 'A'+ c - 'a';
		}
	
		adr = lseek(in,-1,SEEK_CUR);
		write(in,&c,1);
	}
	close(in);

	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);
}
