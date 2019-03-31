#include <iostream>
using namespace std;

class CQueue{
private:
	char *Queue;
	int capacity;
	int QueueFront;
	int QueueBack;
public:
	CQueue(int capacity);
	int size();
	void push(char ch);
	char pop();
	bool empty();
	bool full();
	int getBack();
	int getFront();
	int getCapacity();
};
CQueue::CQueue(int capacity){
	QueueFront = 0;
	QueueBack = 0;

	if (capacity <= 0)
		this->capacity = 1;
	else if (capacity >= 100)
		this->capacity = 100;
	else
		this->capacity = capacity;
	
	Queue = new char[capacity];
}
void CQueue::push(char ch){
	Queue[QueueBack] = ch;
	QueueBack++;
}
char CQueue::pop(){
	char temp = Queue[QueueFront];
	QueueFront++;
	return temp;
}
int CQueue::size(){
	return QueueBack - QueueFront;
}
bool CQueue::empty(){
	if (QueueFront == QueueBack)
		return true;
	else
		return false;
}
bool CQueue::full(){
	if (size() + 1 == capacity)
		return true;
	else
		return false;
}
int CQueue::getBack(){ return QueueBack; }
int CQueue::getFront(){ return QueueFront; }
int CQueue::getCapacity(){ return capacity; }

int main(){
	char ch = 'G';
	CQueue cq(10);
	cq.push('A');
	cout << "Push : " << "A" << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push('B');
	cout << "Push : " << "B" << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push('C');
	cout << "Push : " << "C" << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push('D');
	cout << "Push : " << "D" << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;

	cout << "Pop  : " << cq.pop() << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cout << "Pop  : " << cq.pop() << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cout << "Pop  : " << cq.pop() << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;

	cout << "capacity :  " << cq.getCapacity() << ", size : " << cq.size() << endl << endl;

	cq.push(ch++);
	cout << "Push : " << char(ch - 1) << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push(ch++);
	cout << "Push : " << char(ch - 1) << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push(ch++);
	cout << "Push : " << char(ch - 1) << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push(ch++);
	cout << "Push : " << char(ch - 1) << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;
	cq.push(ch++);
	cout << "Push : " << char(ch - 1) << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;

	while (!cq.empty())
		cout << "Pop  : " << cq.pop() << ",  Front :  " << cq.getFront() << ",  Back : " << cq.getBack() << endl;

}