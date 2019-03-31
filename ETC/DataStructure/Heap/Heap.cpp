#include <iostream>
using namespace std;

void swap(int* a, int* b){
	int temp = 0;
	temp = *a;
	*a = *b;
	*b = temp;
}

class MaxHeap{
public:
	int size = 10;
	int *arr = new int[], *temp;;
	
	int SIZE(){ return size; }
	void MakeHeap(int *numbers,int index,int size);
	void sort();
	int top();
	int pop();
	void push(int *arr[]);
	void initialize(int *array[], int Size);
	void output();
	void deactivateArray();
	~MaxHeap(){ delete[] arr; }
};
void MaxHeap::MakeHeap(int *numbers, int index, int size){
	int root = index;
	int child = 0;

	while (root * 2 + 1 <= size){
		child = root * 2 + 1;

		if (child + 1 <= size)
		if (numbers[child] < numbers[child + 1])
			child++;

		if (numbers[root] < numbers[child])
			swap(numbers + root, numbers + child);
		else
			break;
		root = child;
	}
}
void MaxHeap::sort(){

	for (int i = size / 2; i >= 0; i--)
		MakeHeap(arr, i, size - 1);

	for (int i = 1; i < size; i++){
		swap(arr + size - i, arr);
		MakeHeap(arr, 0, size - i - 1);
	}

}
int  MaxHeap::top(){
	return arr[0];
}
int  MaxHeap::pop(){ return 0; }
void MaxHeap::push(int *arr[]){}
void MaxHeap::initialize(int *array[], int Size){
	for (int i = 0; i < Size; i++)
		arr[i] = *array[i];

}
void MaxHeap::output(){
	cout << "output data : ";
	for (int k = 0; k < size; k++)
		cout << arr[k] << " ";
}
void MaxHeap::deactivateArray(){
	for (int i = 0; i < size; i++)
		arr[i] = NULL;
	size = 0;
}
int main()
{
	MaxHeap a;

	cout << "Heap sort example : " << endl;
	cout << "# of dataset : ";
	cin >> a.size;

	cout << "In put data : ";
	for (int k = 0; k < a.size; k++)
		cin >> a.arr[k];

	a.sort();

	a.output();
	
	return 0;
}
