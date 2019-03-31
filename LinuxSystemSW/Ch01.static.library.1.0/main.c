#include "include.h"
#include "mylib.h"

//#############################################################################
// Request: Complete the following functions. 
// Due    : Sep. 09, 2015 15:00
//#############################################################################



//#############################################################################
// Complete the functions which are defined int the file [mylib.c]
/*
int my_min(int *list, int max);
int my_max(int *list, int max);
int my_sum(int *list, int max);
double my_mean(int *list, int max);
double my_stdv(int *list, int max);
*/

//###################################################################################
void my_print(int* list, int max)
{
	int i;

	printf("--------------------------------------------------\n");
	for(i=0; i<max; i++) printf("[%3d] [%5d]\n", i, list[i]);
	printf("--------------------------------------------------\n");
}


//###################################################################################
int main(int argc, char ** argv)
{
	int *list, max, i;

	srand(time(NULL));
	max = rand()%10 +10;
	list = malloc(sizeof(int) * max);
	
	for(i=0; i<max; i++) list[i] = rand() % 1000;
	
	my_print(list, max);


	printf("total count         : %4d\n",   max );
	
	printf("value min           : %4d\n",   my_min(list, max) );
 
	printf("value max           : %4d\n",   my_max(list, max) );
	
	printf("value sum           : %4d\n",   my_sum(list, max) );

	printf("value mean          : %7.2f\n", my_mean(list, max) );

	printf("value std deviation : %7.2f\n", my_stdv(list, max) );


	free(list);

	return EXIT_SUCCESS;
}

