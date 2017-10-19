#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>




//#############################################################################
// Request: Complete the following functions. 
// Due    : Nov. 18, 2015 21:00
//#############################################################################


// https://en.wikipedia.org/wiki/Matrix_multiplication

// 0. Matrix Multifilcation: g_Mab = g_Ma x g_Mb
// 1. Create a number of threads same to the number of elements of matrix g_Mab
// 2. Each Thread calculates the value of an element in g_Mab simultaneously.
//
// 3. The size of matrix g_Ma is given with the grguments. ex. ]./ret <row> <column>
// 4. Then the size of matrix g_Mb is <column> x <row>
// 5. The elements of g_Ma and g_Mb are automatically set with random number between 0 and 3.
//
// 6. The size of matrix g_Mab is <row> x <row> 
// 7. You can consult the detail of matrix multificaitoin to the link below
//		http://en.wikipedia.org/wiki/Matrix_multiplication
//
// 8. be in mind that there is a limit in the number of threads created at the same time.
//		max number of threads is 304, which is emperically tested.

// 9. Q: make the execution time (real time) less than 5 seconds
//			You should use the single_multiflication() function to get the value of each elements in g_Mab


#define MAX_ROW		100
#define MAX_COLUMN	100
#define MAX_VALUE	3
#define MAX_THREAD 10000

int g_Ma[MAX_ROW][MAX_COLUMN], g_Mb[MAX_ROW][MAX_COLUMN], g_Mab[MAX_ROW][MAX_COLUMN];
int g_row=0, g_column=0;

//#############################################################################
void print_matrix(int M[MAX_ROW][MAX_COLUMN], int max_row, int max_column) 
{
	int row, column;

	printf("\n");	
	for(row=0; row<max_row; row++)
	{
		for(column=0; column<max_column; column++)
			printf("%4d", M[row][column]);
		printf("\n");
	}

}


//#############################################################################
int g_value = 0;
void make_matrix(int M[MAX_ROW][MAX_COLUMN], int max_row, int max_column) 
{
	int row, column;

	for(row=0; row<max_row; row++)
		for(column=0; column<max_column; column++)
			M[row][column] = g_value++%MAX_VALUE; //rand()%MAX_VALUE;
}


//#############################################################################
int single_multiflication(int row, int column)
{
	int value = 0;

	for(int i=0; i<g_column; i++)
	{
		value += g_Ma[row][i] * g_Mb[i][column];
		usleep(10000);
	}
	return value;
}


//#############################################################################
void *thread_function(void *arg) 
{
	int *num = (int *)arg;
	g_Mab[num[0]][num[1]] = single_multiflication(num[0],num[1]);
	/*
	int r,c,v;
	v = (int)arg;

	r = v / g_row;
	c = v % g_row;
	g_Mab[r][c] = single_multiflication(r,c);
	pthread_exit(0);
	*/
}


//#############################################################################
int main(int argc, char **argv)
{
	int num[2];

	if (argc != 3)
	{
		printf("USAGE: ] ./ret <row> <column>\n");
		exit(0);
	}
	memset(g_Ma, 0, sizeof(int)*MAX_ROW*MAX_COLUMN);
	memset(g_Mb, 0, sizeof(int)*MAX_COLUMN*MAX_ROW);
	memset(g_Mab, 0, sizeof(int)*MAX_ROW*MAX_ROW);

	srand( time(NULL) );

	g_row = atoi(argv[1]);
	g_column = atoi(argv[2]);

	make_matrix(g_Ma, g_row, g_column);
	make_matrix(g_Mb, g_column, g_row);

	print_matrix(g_Ma, g_row, g_column);
	print_matrix(g_Mb, g_column, g_row);
/*
pthread_t thread[MAX_THREAD];
int num_thread = grow * g_row;
int i,j.rew,r,c;
for(j=0,i=0 ; i<num_thread ; i++){
	res = pthread_create(&a_thread[i],NULL,thread_function,(void *)i);
	if(res != 0){
		for(; j<i ; i++)
		res = pthread_join(a_thread[i],NULL);
		if(res != 0){
			perror("thread join fail");
			exit(EXIT_FAILURE);
			}
			}
			}
			}
*/
	int res,i,j;
	pthread_t thread[g_row*g_row];
	void *thread_result;

	for(i = 0 ; i<g_row*g_row ; i++){
			num[0] = i / g_row;
			num[1] = i % g_row;
			res = pthread_create(&thread[i],NULL,thread_function,(void *)num);
			usleep(1000);
			//res = pthread_join(thread[i],NULL);
	}
	for(i = 0 ; i<g_row*g_row ; i++){
			res = pthread_join(thread[i],NULL);
	}

	
	print_matrix(g_Mab, g_row, g_row);


	printf("Execution finished successfully.... \n\n");

}
