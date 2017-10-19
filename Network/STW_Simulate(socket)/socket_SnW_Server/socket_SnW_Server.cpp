#include <winsock2.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define BUFSIZE 512

#define TIMEOUT 5
#define MAX_SEQ 1
#define TOT_PACKETS 8
#define inc(k) if(k<MAX_SEQ) k++; else k=0;
typedef struct
{
	int data;
}packet;
typedef struct
{
	int kind;
	int seq;
	int ack;
	packet info;
	int err;
}frame;
frame DATA;
typedef enum{ frame_arrival, err, timeout, no_event } event_type;

void err_quit(char *msg);
void err_display(char *msg);
void from_network_layer(packet *);
void to_network_layer(packet *);
void to_physical_layer(frame *);
void from_physical_layer(frame *);
void wait_for_event_sender(event_type *);
void wait_for_event_reciever(event_type *);
int reciever();
packet sender();
int random(int n);

int i = 1;         //Data to be sent by sender
char turn;      //r , s
int DISCONNECT = 0;
char temp_s[BUFSIZE + 1];
char temp_c[BUFSIZE + 1];
char temp[BUFSIZE + 1];
char temp_ack[BUFSIZE + 1];
char temp_frame[BUFSIZE + 1];
char tmp[BUFSIZE + 1];
int error_r = 0, error_s = 0;

int main(int argc, char* argv[])
{
	int retval;
	packet sf;
	int ra;
	srand((unsigned)time(NULL));

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(9000);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	retval = bind(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("bind()");

	// 데이터 통신에 사용할 변수
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];
	char ack[] = { "Ack\0" };
	int n = 0;
	bool err = TRUE;;

	printf("Reciver(Server)\n");

	/*while (!DISCONNECT)
	{
		sender();
		Sleep(10);
		reciever();
		if (error_s == 1){
			error_s--;
			continue;
		}
		if (error_r == 1){
			error_r--;
		}
		strcat_s(temp_s,temp_c);
		puts(temp_s);
	}
	puts(temp);*/

	// 클라이언트와 데이터 통신
	while (n<10){
		sender();
		// 데이터 받기
		addrlen = sizeof(clientaddr);
		retval = recvfrom(sock, (char*)&sf,sizeof(sf), 0, (SOCKADDR *)&clientaddr, &addrlen);
		printf("s = %d\n", sf);

		// 받은 데이터 출력
		puts(temp_frame);

		/*if (error_s == 1){
			error_s--;
			continue;
		}
		else if (error_r == 1)
			error_r--;*/

		ra = reciever();
		// 데이터 보내기
		retval = sendto(sock, (char*)&ra, sizeof(ra), 0, (SOCKADDR *)&clientaddr, sizeof(clientaddr));
		printf("r = %d\n", ra);
		//puts(temp_c);

		n++;
	}

	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();
	return 0;
}

void err_quit(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCTSTR)msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(-1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

packet sender()
{
	static int frame_to_send = 0;
	static frame s;
	packet buffer;
	event_type event;
	static int flag = 0;

	if (flag == 0)
	{
		from_network_layer(&buffer);
		s.info = buffer;
		s.seq = frame_to_send;
		sprintf_s(temp_s, "SENDER :  Frame = %d    Ack No = %d     ", s.info, s.seq);
		turn = 'r';
		to_physical_layer(&s);
		flag = 1;
	}
	wait_for_event_sender(&event);
	if (turn == 's')
	{
		if (event == frame_arrival)
		{
			from_network_layer(&buffer);
			inc(frame_to_send);
			s.info = buffer;
			s.seq = frame_to_send;
			sprintf_s(temp_s, "SENDER :  Frame = %d    Ack No = %d     ", s.info, s.seq);
			turn = 'r';
			to_physical_layer(&s);
		}
		if (event == timeout)
		{
			sprintf_s(temp_s, "SENDER : Time Out!Resending Frame    ");
			turn = 'r';
			to_physical_layer(&s);
		}
	}
	return s.info;
}
/*__________________________________________________________________________*/
int reciever()
{
	static int frame_expected = 0;
	frame r, s;
	event_type event;

	wait_for_event_reciever(&event);
	if (turn == 'r')
	{
		if (event == frame_arrival)
		{
			from_physical_layer(&r);
			if (r.seq == frame_expected)
			{
				to_network_layer(&r.info);
				inc(frame_expected);
			}
			else
				sprintf_s(temp_c, "RECIEVER : Acknowledgement Resent\n");

			turn = 's';
			to_physical_layer(&s);
		}
		if (event == err)
		{
			sprintf_s(temp_c, "RECIEVER : Garbled Frame\n");
			turn = 's';     //if frame not recieved
		}                 //sender shold send it again
	}
	return frame_expected;
}
/*__________________________________________________________________________*/
void from_network_layer(packet *buffer)
{
	(*buffer).data = i;
	i++;
}
/*___________________________________________________________________________*/
void to_physical_layer(frame *s)
{                     // 0 means error
	s->err = random(4);  //non zero means no error
	DATA = *s;           //probability of error = 1/4
}
/*___________________________________________________________________________*/
void to_network_layer(packet *buffer)
{
	sprintf_s(temp_c, "RECIEVER :Packet %d recieved , Ack Sent\n", (*buffer).data);
	if (i>TOT_PACKETS)          //if all packets recieved then disconnect
	{
		DISCONNECT = 1;
		printf("\nDISCONNECTED");
	}
}
/*___________________________________________________________________________*/
void from_physical_layer(frame *buffer)
{
	*buffer = DATA;
}
/*___________________________________________________________________________*/
void wait_for_event_sender(event_type * e)
{
	static int timer = 0;

	if (turn == 's')
	{
		timer++;
		if (timer == TIMEOUT)
		{
			*e = timeout;
			timer = 0;
			return;
		}
		if (DATA.err == 0){
			*e = err;
			error_s++;
		}
		else
		{
			timer = 0;
			*e = frame_arrival;
		}
	}
}
/*____________________________________________________________________________*/
void wait_for_event_reciever(event_type * e)
{
	if (turn == 'r')
	{
		if (DATA.err == 0){
			*e = err;
			error_r++;
		}
		else
			*e = frame_arrival;
	}
}
/*____________________________________________________________________________*/
int random(int n){
	return rand() % n;
}
