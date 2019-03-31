#include <iostream>
using namespace std;

class Stack{
private :
	int Top;
	int Capacity; //스택의 용량
	int *arr;
public :
	Stack(){
		cout << "Stack의 용량을 지정하시오 : ";
		cin >> Capacity;
		arr = new int [Capacity];
		Top = -1;
		}
	~Stack() { delete[] arr; }
	bool empty();
	int size();
	void pop();
	void push(int element);
	int top();
	void setTop(){ cout << "Top " << Top << endl; }

};

bool Stack :: empty(){
	if (Top <= -1)
		return true;
};
int Stack::size(){
	return Top+1;
};
void Stack::pop(){
	if (Top >= 0)
		Top--;
};
void Stack::push(int element){
	if (Capacity == Top+1)
		cout << "Stack is Full" << endl;
	else{
		arr[Top + 1] = element;
		Top++;
	}
};
int Stack::top(){
	int &top = arr[Top];
	return top;
};

int main(){
	Stack a;
	cout << "------------------------ " << endl;
	cout << "empty " << a.empty() << endl;
	a.setTop();
	cout << "------------------------ " << endl;
	for (int i = 0; i < 6; i++){
		a.push(i);
		cout << "Top  " << a.top() << endl;
		cout << a.size() << endl;
	}
	cout << "------------------------ " << endl;
	cout << "empty " << a.empty() << endl;
	a.setTop();
	cout << "------------------------ " << endl;
	for (int i = 0; i < 5; i++){
		cout << "Top  " << a.top() << endl;
		a.pop();
		cout << a.size() << endl;
	}
	cout << "------------------------ " << endl;
	cout << "empty " << a.empty() << endl;
	a.setTop();
	cout << "------------------------ " << endl;
}