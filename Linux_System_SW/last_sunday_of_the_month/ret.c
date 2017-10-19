//Q: Complete the get_the_last_sunday_of_the_month() which returns 
//   the date of the last Sunday of a given month.
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
int get_the_last_sunday_of_the_month(int year, int month)
{
	struct tm tm_a, *tm_ptr;
	time_t tv_a;
	int day = 0,sec = 60*60*24;
	int day_end[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	
	memset(&tm_a, 0, sizeof(struct tm));
	tm_a.tm_year = year - 1900;
	tm_a.tm_mon = month-1;
	tm_a.tm_mday = 1;
	tv_a= mktime(&tm_a);
	tm_ptr = localtime(&tv_a);

	while(1){
		tm_ptr = localtime(&tv_a);
		if(tm_ptr->tm_wday == 0)
			day = tm_ptr->tm_mday;
	
		tv_a += sec;

		if(tm_ptr->tm_mday == day_end[month])	
			break;	
		}

	return day;
}



//#############################################################################
int main(int argc, char **argv)
{
	int year, month;
	if (argc != 1)
	{
		printf("USAGE: ] ret\n");
		exit(0);
	}

	year = 2010; month=1;
	printf("The last sunday of %04d_%02d is [%2d]\n", year, month, get_the_last_sunday_of_the_month(year, month));


	year = 2010; month=2;
	printf("The last sunday of %04d_%02d is [%2d]\n", year, month, get_the_last_sunday_of_the_month(year, month));


	year = 2010; month=3;
	printf("The last sunday of %04d_%02d is [%2d]\n", year, month, get_the_last_sunday_of_the_month(year, month));


	year = 2010; month=4;
	printf("The last sunday of %04d_%02d is [%2d]\n", year, month, get_the_last_sunday_of_the_month(year, month));


}
