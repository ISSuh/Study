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
// Due    : 2015-09-30 21:00
//#############################################################################


// Implement the following shell command using high-level file functions
// ] wc infile
//


// You should use the follwing high-level I/O functions 
// to read from and write to files.
// ex. fopen(), fclose(), scanf(), printf(), gets(), puts(), fread(), fwrite(), ...
//
// good luck!


//#############################################################################
int main(int argc, char **argv)
{
	int count_line=0,count_word=0,count_byte=0,i;
	char line[10240];
	FILE *in;

	in = fopen("infile","r");
	while((fgets(line,10240,in)) != 0)
	{
		count_line++;
		
		for(i=0 ; line[i] != '\0' ; i++ )
		{
			if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'){
				if(line[i+1] != ' ')
					count_word++;
			}
	
		}
		count_byte += i;
	}
	fclose(in);

	printf(" %d  %d  %d infile\n",count_line,count_word,count_byte);
	printf("Execution finished successfully.... \n\n");
    exit(EXIT_SUCCESS);
}
