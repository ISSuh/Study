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
#include <dirent.h>



//#############################################################################
// Request: Complete the following program. 
// Due    : 2015-10-07 24:00
//#############################################################################


//  Complete the following C program which print out the max depth from the given dir.

// ] ./ret .
// ] Max Depth = 14

// ] ./ret /home
// ] Max Depth = 14

// good luck!




//#############################################################################
int max = 0;
int printdir(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
	int depth_count = depth/4; 

	if(depth_count > max)
			max = depth_count;

    if((dp = opendir(dir)) == NULL) {
        fprintf(stderr,"cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL) {
        lstat(entry->d_name,&statbuf);
        if(S_ISDIR(statbuf.st_mode)) {
            if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
                continue;
            printdir(entry->d_name,depth+4);
        }
    }
    chdir("..");
    closedir(dp);
}

int main(int argc, char* argv[])
{
    char *topdir, pwd[2]=".";
    if (argc != 2)
        topdir=pwd;
    else
        topdir=argv[1];

    printf("Directory scan of %s\n",topdir);
	printdir(topdir,0);
	printf("Max Depth = %d\n",max);
    printf("done.\n");

    exit(0);
}