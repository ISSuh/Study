#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>




//#############################################################################
// Request: Complete the following program. 
// Due    : 2015-09-23 15:00
//#############################################################################


// Implement the following shell command using low-level file functions
// ] split -l 10 infile

// You should use the follwing low-level I/O functions 
// to read from and write to files.
// write(), read(), open(), close()
//
// good luck!



//#############################################################################
int main(int argc, char **argv)
{
	char c;
	char file_name[4] = {"xaa"};
	int count = 0;
	int i = 0,j = 0,in,out;

	in = open("infile", O_RDONLY);
	out = open(file_name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
	while(read(in,&c,1) == 1){
		write(out,&c,1);

		if (c == '\n'){
			count++;
		if(count == 10){
			
			if (i == 25)
			{
				j++;
				file_name[1] = 'a' + j;
				file_name[2] = 'a';
				i = 0;
			}
			else{
				i++;
				file_name[2]= 'a' + i;
			}
			out = open(file_name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
			count = 0;
		}
		}
	}
	close(in);
	close(out);

	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);
}
