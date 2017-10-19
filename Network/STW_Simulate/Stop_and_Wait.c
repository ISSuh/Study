#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define PACKET_NUM 5 // ������ ���� ����

typedef struct {
	int data;
}packet; // ��Ŷ����ü ����
typedef struct {
	int seq; // Sender������ ������ȣ(seq)
	int ack; // Receiver������ ack
	packet info; // �����ӳ��� ������
	int err; // ���� �߻��� ���̱� ���� ����
}frame; // ������ ����ü ����

typedef enum{ ARRIVAL, ERR, TIMEOUT } event_type; // �����ӵ���, Time out, ���� �̺�Ʈ ���� 

void FromNetworkLayer(packet *); // ��Ʈ��ũ������ �����͸� ����
void ToPhysicalLayer(frame *); // �����ӱ�����, ���������� ����
void FromPhysicalLayer(frame *); // ���۹��� �����͸� ���������� �����͸�ũ������ ����
void ToNetworkLayer(packet *); // �������� ��Ʈ��ũ������ ����
void WaitSender(event_type *); // Sender������ Timer,����,������ Ȯ��
void WaitReciever(event_type *); // Receiver������ ������ ���� Ȯ��
void sender(); // Sender ����
void reciever(); // Receiver ����
int Random(int n); // �������� ������ �߻��ϱ����� �Լ�
int MakeSeq(packet *, int*); // Sender������ ������ȣ(seq)�� ��������� �Լ�

int i = 0; // �����ϴ� ��Ŷ�� ��ȣ
char turn = 's'; // Sender,Receiver�� ���� 
int Finish = 0; // �������
frame DATA; // ���۵Ǵ� ������

void main(){
	srand((unsigned)time(NULL));

	printf("Sample  > SENDER : Data[] Seq[]        RECEIVER : Data[] Ack[] \n\n");

	while (!Finish){
		sender();
		Sleep(300);
		reciever();
	}
	_getch();
}

void sender(){
	static int seq = 0; // ������ȣ 
	static frame s; // Sender������ �����̹� 
	packet buffer; // ��Ʈ��ũ������ ���� ��Ŷ
	event_type event; // ������ ������ 3���� �̺�Ʈ
	static int flag = 0;

	if (flag == 0){ // ������ ������ ���� �ѹ� ����
		FromNetworkLayer(&buffer); // ��Ʈ��ũ������ ��Ŷ�� ����
		s.info = buffer; // ���� �����͸� ����
		s.seq = seq; // ������ȣ
		printf("SENDER :  Data[%d]   Seq[%d]        ", s.info, s.seq);
		turn = 'r'; // Receiver�� ���ʷ� �Ѿ�� ��
		ToPhysicalLayer(&s); // ���������� �����͸� �ѱ�
		flag = 1;
	}

	WaitSender(&event); // � �̺�Ʈ�� �߻��ϴ��� ����

	if (turn == 's'){ // Sender�� ����
		if (event == ARRIVAL){ // �������� ����. �̺�Ʈ ARRIVAL�߻�
			FromNetworkLayer(&buffer); // ��Ʈ��ũ������ ��Ŷ�� ����
			MakeSeq(&buffer, &seq); // ���� ��Ŷ�� �̿��Ͽ� ������ȣ(seq)�� ����
			s.info = buffer; // ���� �����͸� ����
			s.seq = seq; // ������ȣ(seq) ����
			printf("SENDER :  Data[%d]   Seq[%d]	  ", s.info, s.seq);
			turn = 'r'; // Receiver�� ���ʷ� �Ѿ�� ��
			ToPhysicalLayer(&s); // ���������� �����͸� �ѱ�
		}

		else if (event == TIMEOUT){ // �̺�Ʈ Timeout �߻�
			printf("SENDER : Time Out! Resending Frame");
			turn = 'r'; // Receiver�� ���ʷ� �Ѿ�� ��
			ToPhysicalLayer(&s); // ���������� �ٽ� �����͸� �ѱ�
		}
	}
}

void reciever(){
	static int ack = 1; // Receiver���� ������ ack
	frame r, s; // ���� ������, �ٽ� ���� ������ ����
	event_type event; // �̺�Ʈ

	WaitReciever(&event); // ��̺�Ʈ�� �߻��ϴ��� ����

	if (turn == 'r'){ // Receiver�� ����
		if (event == ARRIVAL){ // �������� ����. �̺�Ʈ ARRIVAL �߻�
			FromPhysicalLayer(&r); // ���������� �����͸� ����

			if (r.seq + 1 == ack || r.seq - 1 == ack){ // ���� ��Ŷ�� ������ȣ�� ���� ���� ack�� ������ �Ǵ�
				printf("   RECIEVER : Data[%d] Received Ack[%d] Send\n", r.info, ack);
				ToNetworkLayer(&r.info); // ��Ʈ��ũ������ �����͸� ����

				if (ack < 1)
					ack++;
				else
					ack = 0; // ack�� 0�Ǵ� 1�� �ǵ��� ��.
			}

			else
				printf("   RECIEVER : Ack Resent(Discard Frame)\n");

			turn = 's'; // Sender ���ʷ� �ٲ�
			ToPhysicalLayer(&s); // ack�� �����ϱ����� ���������� �����͸� ����
		}

		if (event == ERR){ // ������ �߻�������
			printf("   RECIEVER : Frame Loss!\n");
			turn = 's'; // �������� �߰��� �Ҿ���ȴٸ� ���ʸ� Sender�� �ٲ��༭ �ٽ� �������� ��
		}
	}
}



void FromNetworkLayer(packet *buffer){ // ��Ʈ��ũ������ �����͸�ũ������ ��Ŷ�� �ֱ����� �����͸� ����
	(*buffer).data = i; // �����ʹ� 1,2,3...n
	i++;
}

void ToPhysicalLayer(frame *s){ // �����͸�ũ������ ���������� �����͸� ����
	s->err = Random(5); // 20%�� Ȯ��� ������ �����ȴ�. 0�϶� ������� ������
	DATA = *s;
}

void FromPhysicalLayer(frame *buffer){ // Receiver�� ���������� �����͸� ���۹���
	*buffer = DATA;
}

void ToNetworkLayer(packet *buffer){ // Receiver�� �����͸�ũ������ ��Ʈ��ũ������ �����͸� ����
	if (i == PACKET_NUM){ // ���۹��� i�� �������� ���̸�ŭ�̸� ���� �Ϸ��̹Ƿ� ����
		Finish = 1;
		printf("\nDISCONNECTED");
	}
}

void WaitSender(event_type * e){ // Sender���� �̺�Ʈ ����
	static int timer = 0; // Ÿ�̸� ����

	if (turn == 's'){ // Sender�� �����϶�
		timer++; // Ÿ�̸Ӹ� ���� ��Ŵ

		if (timer == 5){ // Ÿ�̸Ӱ� �����ɵ��� ack�� �����ʴ´ٸ� �̺�Ʈ�� TIMEOUT���� ����
			*e = TIMEOUT;
			timer = 0;
			return;
		}

		if (DATA.err == 0) // ���������ۿ� ������ �ִٸ� �̺�Ʈ�� ERR�� ����
			*e = ERR;
		else{ // ���������� �������� �����ߴٸ� ARRIVAL���� ����
			timer = 0;
			*e = ARRIVAL;
		}
	}
}

void WaitReciever(event_type * e){ // Receiver������ �̺�Ʈ ����
	if (turn == 'r'){ // Receiver�����϶�
		if (DATA.err == 0) // ������ �����϶�
			*e = ERR; // �̺�Ʈ�� ERR�� ����
		else // �ƴҰ�� �������̹Ƿ� ARRIVAL�� ����
			*e = ARRIVAL;
	}
}

int Random(int n){
	return rand() % n; // ������ �����ϰ� ����
}
int MakeSeq(packet *buffer, int *seq){
	*seq = buffer->data % 2; // ������ ������(���⼭�� �����Ͱ� ex)1,2,3...n)�� �̿��� ��ⷯ 2�����Ͽ� ������ȣ(seq)�� ������
	return *seq;
}
