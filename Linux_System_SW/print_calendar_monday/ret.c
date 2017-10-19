//Q:	Complete the print_calendar() which print the calendar of a given month and  year.
//		- Display Monday as the first day of the week.
//		- Example output of print_calendar(2016, 8).
//
//
//	               8 2016 
//	   Mon  Tue  Wed  Thu  Fri  Sat  Sun
//       1    2    3    4    5    6    7
//       8    9    10  11   12   13   14 
//      15   16   17   18   19   20   21
//	    22   23   24   25   26   27   28
//	    29   30   31

// The print_calendar() is equivalent to the Linux command cal, as follows.
// ] cal -m 8 2016
//


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>



//#############################################################################
// complete this function
void print_calendar(int year, int month)
{
	struct tm *tm_ptr,tm_str;
	time_t the_time;
	int day_start = 1,day_start_week,i,temp;
	int day_end[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

	
	if (year%4 == 0 && year%100 != 0 || year%400 == 0)
		day_end[2] = 29;
		
	memset(&tm_str,0, sizeof(struct tm));
	tm_str.tm_year = year - 1900;
	tm_str.tm_mon = month-1;
	tm_str.tm_mday = 1;
	the_time = mktime(&tm_str);
	tm_ptr = localtime(&the_time);
	day_start_week = tm_ptr->tm_wday - 1;
	
	printf("             %d     %d        \n",month,year);
	printf("Mon  Tue  Wed  Thu  Fri  Sat  Sun\n");
	for(i = 0 ; i<day_start_week ; i++){
		printf("     ");
	}
	for (; day_start<=day_end[month] ;i++ )
	{
		printf("  %2d ",day_start++);
		if(i%7 == 6)
			printf("\n");
	}
	printf("\n\n");
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
