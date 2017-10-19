#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>


//I:	Complete the sum_sunday() which returns the date sum of all Sundays in a given year.
//		The return value of date_sum(2016) is 826.
//		826 = (3+10+17+24+31) + (7+14+21+28) + ... + (4+11+18+25)
//
//							2016                               
//
//         1월                    2월                    3월        
// 일 월 화 수 목 금 토   일 월 화 수 목 금 토   일 월 화 수 목 금 토
//                 1  2       1  2  3  4  5  6          1  2  3  4  5
//  3  4  5  6  7  8  9    7  8  9 10 11 12 13    6  7  8  9 10 11 12
// 10 11 12 13 14 15 16   14 15 16 17 18 19 20   13 14 15 16 17 18 19
// 17 18 19 20 21 22 23   21 22 23 24 25 26 27   20 21 22 23 24 25 26
// 24 25 26 27 28 29 30   28 29                  27 28 29 30 31
// 31
//          4월                    5월                    6월        
// 일 월 화 수 목 금 토   일 월 화 수 목 금 토   일 월 화 수 목 금 토
//                 1  2    1  2  3  4  5  6  7             1  2  3  4
//  3  4  5  6  7  8  9    8  9 10 11 12 13 14    5  6  7  8  9 10 11
// 10 11 12 13 14 15 16   15 16 17 18 19 20 21   12 13 14 15 16 17 18
// 17 18 19 20 21 22 23   22 23 24 25 26 27 28   19 20 21 22 23 24 25
// 24 25 26 27 28 29 30   29 30 31               26 27 28 29 30
// 
//          7월                    8월                    9월        
// 일 월 화 수 목 금 토   일 월 화 수 목 금 토   일 월 화 수 목 금 토
//                 1  2       1  2  3  4  5  6                1  2  3
//  3  4  5  6  7  8  9    7  8  9 10 11 12 13    4  5  6  7  8  9 10
// 10 11 12 13 14 15 16   14 15 16 17 18 19 20   11 12 13 14 15 16 17
// 17 18 19 20 21 22 23   21 22 23 24 25 26 27   18 19 20 21 22 23 24
// 24 25 26 27 28 29 30   28 29 30 31            25 26 27 28 29 30
// 31
//         10월                   11월                   12월        
// 일 월 화 수 목 금 토   일 월 화 수 목 금 토   일 월 화 수 목 금 토
//                    1          1  2  3  4  5                1  2  3
//  2  3  4  5  6  7  8    6  7  8  9 10 11 12    4  5  6  7  8  9 10
//  9 10 11 12 13 14 15   13 14 15 16 17 18 19   11 12 13 14 15 16 17
// 16 17 18 19 20 21 22   20 21 22 23 24 25 26   18 19 20 21 22 23 24
// 23 24 25 26 27 28 29   27 28 29 30            25 26 27 28 29 30 31
// 30 31
		

// Due: 2015-10-14 15:00


//#############################################################################
// complete this function
int sum_sunday(int year)
{
	int sum = 0;
	struct tm *tm_ptr,tm_str;
	time_t the_time;
	int i = 1,sec = 60*60*24;

	memset(&tm_str,0, sizeof(struct tm));
	tm_str.tm_year = year - 1900;
	tm_str.tm_mon = 0;
	tm_str.tm_mday = 1;
	the_time = mktime(&tm_str);
	tm_ptr = localtime(&the_time);

	while(i){
		tm_ptr = localtime(&the_time);
		if(tm_ptr->tm_wday == 0)
			sum += tm_ptr->tm_mday;
		the_time += sec;
		
		if (tm_ptr->tm_mon == 11){
			if(tm_ptr->tm_mday == 31)	
				break;	
		}
	}

	return sum;

}

//#############################################################################
int main(int argc, char **argv)
{
	int year;

	if (argc != 1)
	{
		printf("USAGE: ] ret\n");
		exit(0);
	}

	year=2011; printf("Year:%d = %d\n", year, sum_sunday(year));
	year=2012; printf("Year:%d = %d\n", year, sum_sunday(year));
	year=2013; printf("Year:%d = %d\n", year, sum_sunday(year));
	year=2014; printf("Year:%d = %d\n", year, sum_sunday(year));
	year=2015; printf("Year:%d = %d\n", year, sum_sunday(year));
	year=2016; printf("Year:%d = %d\n", year, sum_sunday(year));
}
