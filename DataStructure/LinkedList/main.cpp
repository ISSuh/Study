#include <stdio.h>
#include "LinkedList.h"

int main(){
	List list;
	int DATA;
	ListInit(&list);

	for (int i = 0; i < 10; i++)
		LInsert(&list,i);

	if (LFirst(&list, &DATA)){
		printf("%d ", DATA);

		while (LNext(&list, &DATA))
			printf("%d ", DATA);
		printf("\n");
	}

	if (LFirst(&list, &DATA)){
		if (DATA % 2 == 0)
			LRemove(&list);

		while (LNext(&list, &DATA)){
			if (DATA % 2 == 0)
				LRemove(&list);
		}
	}

	if (LFirst(&list, &DATA)){
		printf("%d ", DATA);

		while (LNext(&list, &DATA))
			printf("%d ", DATA);
		printf("\n");
	}
}