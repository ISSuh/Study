//Q: Complete the function file_size(). 
//   This function returns the size of a given file in bytes.
//   - Use only low-level file I/O functions.	
//   - To get a good score, you should think of the execution time of your program.


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
// complete this function
int file_size(char *file_name)
{
	int file_size = 0;
	int in,info;
	struct stat statbuf;
	in = open(file_name,O_RDWR);
	info = stat(file_name, &statbuf);

	file_size = statbuf.st_size;
	return file_size;
}



//#############################################################################
int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("USAGE: ] ret <file_name>\n");
		exit(0);
	}

	printf("File name  = [%s]\n", argv[1]);
	printf("File size  = [%d]\n", file_size(argv[1]));
}
