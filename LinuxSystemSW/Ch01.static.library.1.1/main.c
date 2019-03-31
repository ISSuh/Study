#include "include.h"
#include "mylib.h"


//#############################################################################
// Request: Complete the following functions. 
// Due    : Sep. 16, 2015 15:00
//#############################################################################



//#############################################################################
// Complete the functions which are defined int the file [mylib.c]
/*
int my_min(int *list, int max);
int my_max(int *list, int max);
int my_sum(int *list, int max);
double my_mean(int *list, int max);
double my_stdv(int *list, int max);

int my_median(int *list, int max);       // the (max/2)-th smallest value
int my_nth_min(int *list, int max, int i);
int my_nth_max(int *list, int max, int i);

int my_freq_most(int *list, int max);	 // # of occurance of the most value which mostely appears in this list. 
int my_freq_least(int *list, int max);	 // # of occurance of the least value which leastly appears in the list.
int my_unique_count(int *list, int max); // # of unique values 
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
	max = rand()%20 +10;
	list = malloc(sizeof(int) * max);
	
	for(i=0; i<max; i++) list[i] = rand() % 20;
	
	my_print(list, max);


	printf("total count       : %4d\n",   max );
	
	printf("value min         : %4d\n",   my_min(list, max) );
 
	printf("value max         : %4d\n",   my_max(list, max) );
	
	printf("value sum         : %4d\n",   my_sum(list, max) );

	printf("value mean        : %7.2f\n", my_mean(list, max) );

	printf("value sdev        : %7.2f\n", my_stdv(list, max) );



	printf("value median      : %4d\n",   my_median(list, max) );

	i = rand()%5 + 1;

	printf("value %2d-th min   : %4d\n",  i, my_nth_min(list, max, i) );

	printf("value %2d-th max   : %4d\n",  i, my_nth_max(list, max, i) );



	printf("most  value count : %4d\n",  my_freq_most(list, max) );

	printf("least value count : %4d\n",  my_freq_least(list, max) );

	//printf("unique value count: %4d\n",  my_unique_count(list, max) );

	free(list);

	return EXIT_SUCCESS;
}

