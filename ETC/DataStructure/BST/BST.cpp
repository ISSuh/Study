#include <iostream>
#include "BinarySearchTree.h"
using namespace std;

int main(){
	BSTREE bstree;

	bstree.BSTMakeAndInit(&(bstree.bst));

	bstree.BSTInsert(&(bstree.bst), 9);
	bstree.BSTInsert(&(bstree.bst), 15);
	bstree.BSTInsert(&(bstree.bst), 31);
	bstree.BSTInsert(&(bstree.bst), 25);
	bstree.BSTInsert(&(bstree.bst), 51);
	bstree.BSTInsert(&(bstree.bst), 93);
	bstree.BSTInsert(&(bstree.bst), 74);
	bstree.BSTInsert(&(bstree.bst), 81);
	bstree.BSTInsert(&(bstree.bst), 41);
	bstree.BSTInsert(&(bstree.bst), 11);

	bstree.BSTShowAll(bstree.bst);
	cout << endl;
	bstree.BSTRemove(&(bstree.bst), 9);
	bstree.BSTShowAll(bstree.bst);
	cout << endl;
	bstree.BSTRemove(&(bstree.bst), 41);
	bstree.BSTShowAll(bstree.bst);
	cout << endl;
	bstree.BSTRemove(&(bstree.bst), 93);
	bstree.BSTShowAll(bstree.bst);
	cout << endl;
	bstree.BSTRemove(&(bstree.bst), 11);
	bstree.BSTShowAll(bstree.bst);
	cout << endl;
	bstree.BSTRemove(&(bstree.bst), 15);
	bstree.BSTShowAll(bstree.bst);
	cout << endl;
}