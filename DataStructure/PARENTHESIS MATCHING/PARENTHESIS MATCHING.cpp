#include <iostream>
#include "stack.h"
#include <string>
using namespace std;
class PM{
public:
	Stack re, le;
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
	PM pm;
	string ex;
	cout << "Type an expresion" << endl;
	cin >> ex;
	cout << "The pairs of matching parentheses in" << endl << ex<< "are" << endl;
	pm.scanning(ex);
}
