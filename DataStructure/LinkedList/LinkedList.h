struct Node{
	int data;
	Node *next;
	Node *prev;
};

struct DLinkedList{
	Node *head;
	Node *tail;
	Node *cur;
	int numOfData;
};

typedef DLinkedList List;

void ListInit(List *plist);
void LInsert(List *plist, int Data);

int LFirst(List *plist, int *pData);
int LNext(List *plist, int *pData);

int LRemove(List *plist);
int LCount(List *plist);