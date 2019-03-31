#include <iostream>
using namespace std;

class Stack{
private:
	int Top;
	int Capacity;
	int *arr;
public:
	Stack(){
		Capacity = 100;
		arr = new int[Capacity];
		Top = -1;
	}
	~Stack() { delete[] arr; }
	bool empty();
	int size();
	void pop();
	void push(int element);
	int top();
};

bool Stack::empty(){
	if (Top <= -1)
		return true;
	else
		return false;
};
int Stack::size(){
	return Top + 1;
};
void Stack::pop(){
	if (Top >= 0)
		Top--;
};
void Stack::push(int element){
	if (Capacity == Top + 1)
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