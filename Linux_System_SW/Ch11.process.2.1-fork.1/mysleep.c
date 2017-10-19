#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>



int main(int argc, char **argv)
{
	int sleep_time = 0;

	if (argc != 2)
	{
		printf("USAGE  : ] ./mysleep [sleep_time]\n");//micro second
		printf("Example: ] ./mysleep 10000 \n");//0.01s
		printf("Example: ] ./mysleep 2000000 \n");//2s

		exit(0);
	}

	sleep_time = atoi(argv[1]);

	printf("%5s: %10d\n", argv[0], sleep_time);
	usleep(sleep_time);		
	printf("%5s: %10d\n", argv[0], sleep_time);
	return 1;
}
