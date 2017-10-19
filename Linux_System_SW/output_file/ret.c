
//Q:	Complete the function all_output_to_single_file(). 
//		This function makes all the output to the screen written to a given file.

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
//redirect all screen output to the file [out]
void all_output_to_single_file(char* out)
{
	int fd;
	close(1);
	close(2);

	fd = open(out,O_RDWR|O_CREAT,0777);
	dup(fd);


}



//#############################################################################
int main(int argc, char **argv)
{	
	all_output_to_single_file("outfile");

	write(1, "STDOUT: Hello World!\n", 22);
	write(2, "STDERR: Hello Error!\n", 22);
}
