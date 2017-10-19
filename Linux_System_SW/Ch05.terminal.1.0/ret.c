//I:	Complete the flowing two functions: void set_terminal() and void reset_terminal()
//		based on the Instructions.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>


//#############################################################################
// Request: complete the following functions. 
// Due    : Oct 28, 2015 18:00
//#############################################################################


struct termios new_set, init_set;

// Complete this function which has the effect of the following Linux command.
// ]$ stty -icanon  min 0 time 20 // 20 * 0.1	 = 2s 
void set_terminal()
{
	tcgetattr(fileno(stdin),&init_set); // 키보드로 부터 입력 받기때문에 파일서술자가 0이여야하니 stdin이여야 한다.
	new_set = init_set;
	new_set.c_lflag &= ~ICANON // ~(ICANON|ISIG|ECHO); 비규범모드
	new_set.c_cc[VMIN] = 0;
	new_set.c_cc[VTIME] = 20;
	tcsetattr(fileno(stdin),TCSANOW,&new_set);
}

// Complete this function which has the effect of the following Linux command.
// ]$ stty sane
void reset_terminal()
{
	tcsetattr(fileno(stdin),TCSANOW,&init_set);
}


//#############################################################################
int main(int argc, char **argv)
{
	char c;
	int count = 0;

	if (argc != 1)
	{
		printf("USAGE: ] ./ret \n");
		exit(0);
	}
	
	set_terminal();

	while( c=getchar() ) // one Char in
	{
		if( c == EOF )
		{
			printf("Enter again: ... %4d\n", count++);
			continue;
		}

		printf("[%c] pressed ...\n", c);
		if( c == 'q') break;
	}

	reset_terminal();

}

