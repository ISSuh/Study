#include <iostream>
#include <string>
#include "Stack.h"
using namespace std;

class Hanoi{
	int *to, *by, *from;
	Stack Tower[10];
public:
	void towerInit(int n);
	void moveDisk(int d, int *to, int *by, int *from);
	void showState();
	Hanoi();
};
Hanoi::Hanoi(){
	int  t, b, f;
	Stack st[10];
	to = &t;
	by = &b;
	from = &f;
}
void Hanoi::towerInit(int n){
	*to = 3;
	*by = 2;
	*from = 1;
	for (int i = 0; i < n; i++)
		Tower[0].push(i);
	moveDisk(n, to, by, from);
}

void  Hanoi::moveDisk(int disk, int *to, int *by, int *from){
	int temp;
	Stack b;
	while (1){
		while (disk > 1){
			b.push(*to);
			b.push(*by);
			b.push(*from);
			b.push(disk);
			disk--;
			temp = *to;
			*to = *by;
			*by = temp;
		}

		Tower[*from - 1].pop();
		Tower[*to - 1].push(disk);
		showState();

		if (!b.empty()){
			disk = b.top();
			b.pop();
			*from = b.top();
			b.pop();
			*by = b.top();
			b.pop();
			*to = b.top();
			b.pop();

			Tower[*from - 1].pop();
			Tower[*to - 1].push(disk);
			showState();

			disk--;
			temp = *from;
			*from = *by;
			*by = temp;
		}
		else
			break;
	}
}
void Hanoi::showState(){
	cout << "Move disk " << Tower[*to - 1].top() << " from tower " << *from << " to top of tower " << *to << endl;
}
class PM{
	Stack re, le;
public:
	void scanning(string expr);
	void printstackstate(int flag);
};

void PM::scanning(string expr){

	for (int i = 0; i < expr.length(); i++){
		if (expr[i] == '('){
			le.push(i);
			printstackstate(i);
		}
		else if (expr[i] == ')'){
			re.push(i);
			printstackstate(i);
		}
	}
}

void PM::printstackstate(int flag){
	if ((le.size() != NULL) && (re.size() != NULL) && (re.top() > le.top())){
		cout << "(" << le.top() << " " << re.top() << ")" << endl;
		re.pop();
		le.pop();
	}

	if ((le.size() != NULL) && (re.size() != NULL) && re.top() < le.top()){
		cout << "No match fo right parenhesis at" << re.top() << endl;
		cout << "No match fo left parenhesis at" << le.top() << endl;
	}
}

int main(){
	Hanoi h;
	PM pm;
	string ex;
	int menu;

	while (1){
		cout << "1. ParenthesisMaching" << endl;
		cout << "2. The Tower of Hanoi" << endl;
		cout << "Selet the Menu : ";
		cin >> menu;
		cout << endl << endl;

		switch (menu){
		case 1:
			cout << "Type an expresion" << endl;
			cin >> ex;
			cout << "The pairs of matching parentheses in" << endl << ex << " are" << endl;
			pm.scanning(ex);
			cout << endl;
			break;
		case 2:
			cout << "Moves for a 6 disk problem are " << endl;
			h.towerInit(6);
			cout << "Moves for a 10 disk problem are " << endl;
			h.towerInit(10);
			cout << endl;
			break;
		}
	}
}