#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 03, 2015 24:00
//#############################################################################



//#############################################################################
// Complete this function which counts the number of processes running on the system
// ] ls /proc | grep ^[0-9] | wc | awk '{print $1}'
// ] ps ax | wc | awk '{print $1}'
// ] watch -n 1 'ls /proc | grep ^[0-9] | wc -l'
// ] watch -n 1 'ps ax | wc -l'
int process_count()
{
	int count=0;
	DIR *dir;
	struct dirent *direntp;
	struct stat statbuf;
	//char ch[20];

	dir = opendir("/proc");
	while((direntp = readdir(dir)) != NULL){
		lstat(direntp->d_name,&statbuf);
		if(S_ISDIR(statbuf.st_mode)){
			//strcpy(ch,direntp ->d_name);
			if('0' <= direntp ->d_name[0] && direntp ->d_name[0] <='9')
				count++;
		}
	}

	closedir(dir);

	return count;
}




//#############################################################################
int main(int argc, char **argv)
{
	int count = 0;

	if (argc != 1)
	{
		printf("USAGE: ] ret \n");
		exit(0);
	}
	

	while( 1 ) 
	{
		printf("Process Count[%3d] : %3d\n", count++, process_count());
		usleep(1000000);
	}

	// ---------------------------------------------

}
