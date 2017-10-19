//Q:	Complete the function find_smallest_file() which find 
//      the smallest file at a given directory.
//		- check all the files in a given directory.
//		- don't need to consider subdirectories.


#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


//#############################################################################
// complete this function

int find_smallest_file(char* dir_name, char* file_name)
{
	DIR *dir;
	struct dirent *direntp; 
	struct stat statbuf;
	int temp[1024],size,min = 2048,i = 0;

	dir = opendir(dir_name);
	while ((direntp = readdir(dir)) != NULL){
		stat(direntp->d_name,&statbuf);
		temp[i] = statbuf.st_size;
		i++;
		if(min > temp[i]){
			min = temp[i];
			strcpy(file_name,direntp->d_name);
		}
	}
	closedir(dir);
}

//#############################################################################
int main(int argc, char **argv)
{
	char dir_name[100]	= "/tmp";
	char file_name[100]	= "I.don't.know";

	strcpy(dir_name, ".");
	find_smallest_file(dir_name, file_name);
	printf("\n");
	printf("dir_name          = [%s]\n", dir_name);
	printf("the smallest file  = [%s]\n", file_name);

	strcpy(dir_name, "/tmp/");
	find_smallest_file(dir_name, file_name);
	printf("\n");
	printf("dir_name          = [%s]\n", dir_name);
	printf("the smallest file  = [%s]\n", file_name);

	strcpy(dir_name, "/etc/");
	find_smallest_file(dir_name, file_name);
	printf("\n");
	printf("dir_name          = [%s]\n", dir_name);
	printf("the smallest file  = [%s]\n", file_name);

}
