//Q: Complete the function file_descriptor() which returns 
//   the file descriptor of a given file stream.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



//#############################################################################
// complete this function
int file_descriptor(FILE* fs) 
{
	int fd=-1;
	
	fd = fileno(fs);  
	return fd;

}



//#############################################################################
int main(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("USAGE: ] ret \n");
		exit(0);
	}

	printf("File descriptor # of stdin  is [%d]\n", file_descriptor(stdin));
	printf("File descriptor # of stdout is [%d]\n", file_descriptor(stdout));
	printf("File descriptor # of stderr is [%d]\n", file_descriptor(stderr));
}
