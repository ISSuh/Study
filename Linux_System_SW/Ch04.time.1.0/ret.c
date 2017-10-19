#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>


//I:	Complete the print_calendar() which print the calendar of a given month and  year.
//		The below is an example output of print_calendar(2016, 8).
//
//
//	               8 2016 
//		Sun  Mon  Tue  Wed  Thu  Fri  Sat
//		      1    2    3    4    5    6    
//		 7    8    9    10  11   12   13   
//		14   15   16   17   18   19   20   
//		21   22   23   24   25   26   27   
//		28   29   30   31

// The print_calendar() is equivalent to the Linux command cal, as follows.
// ] cal 8 2016
//


//#############################################################################
// complete this function
void print_calendar(int year, int month)
{

	//----------------->

	// write your codes here only	
	
	


	//<----------------


}



//#############################################################################
int main(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("USAGE: ] ret\n");
		exit(0);
	}

	print_calendar(2016, 8);
	print_calendar(2016, 9);
	print_calendar(2016, 10);
	print_calendar(2016, 11);

	print_calendar(2016, 12);

}
