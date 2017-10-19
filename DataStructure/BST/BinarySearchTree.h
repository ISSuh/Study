#include <iostream>
using namespace std;

typedef int BSTData;
struct BSTreeNode{
	BSTData data;
	struct BSTreeNode *left;
	struct BSTreeNode *right;
};
class BSTREE{
public:
	BSTreeNode *bst;
	BSTreeNode *MakeBSTreeNode(){
		int i = 10;
		BSTreeNode * node = new BSTreeNode[i];
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	BSTData GetData(BSTreeNode *bst){ return bst->data; }
	void SetData(BSTreeNode *bst, BSTData data){ bst->data = data; }
	BSTreeNode *GetLeftSubTree(BSTreeNode *bst){ return bst->left; }
	BSTreeNode *GetRightSubTree(BSTreeNode *bst){ return bst->right; }
	void MakeLeftSubTree(BSTreeNode *main, BSTreeNode *sub);
	void MakeRightSubTree(BSTreeNode *main, BSTreeNode *sub);
	typedef void (*VisitFuncPtr)(BSTData data);
	void InorderTraverse(BSTreeNode *bst, VisitFuncPtr action);

	BSTreeNode *RemoveLeftSubTree(BSTreeNode *bst){
		BSTreeNode *DNode = NULL;
		if (bst != NULL){
			DNode = bst->left;
			bst->left = NULL;
		}
		return DNode;
	}
	BSTreeNode *RemoveRightSubTree(BSTreeNode *bst){
		BSTreeNode *DNode = NULL;
		if (bst != NULL){
			DNode = bst->right;
			bst->right = NULL;
		}
		return DNode;
	}

	void ChangeLeftSubTree(BSTreeNode *main, BSTreeNode *sub){ main->left = sub; }
	void ChangeRightSubTree(BSTreeNode *main, BSTreeNode *sub){ main->right = sub; }

	void BSTMakeAndInit(BSTreeNode **pRoot){ *pRoot = NULL; }
	void BSTInsert(BSTreeNode **pRoot, BSTData data);

	BSTreeNode *BSTRemove(BSTreeNode **pRoot, BSTData target){
		BSTreeNode *pVRoot = MakeBSTreeNode();
		BSTreeNode *pNode = pVRoot;
		BSTreeNode *cNode = *pRoot; 
		BSTreeNode *dNode;  

		ChangeRightSubTree(pVRoot, *pRoot);

		while (cNode != NULL && GetData(cNode) != target){
			pNode = cNode;
			if (target < GetData(cNode))
				cNode = GetLeftSubTree(cNode);
			else
				cNode = GetRightSubTree(cNode);
		}

		if (cNode == NULL)
			return NULL;

		dNode = cNode;

		if (GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL){
			if (GetLeftSubTree(pNode) == dNode)
				RemoveLeftSubTree(pNode);
			else
				RemoveRightSubTree(pNode);
		}

		else if (GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL){
			BSTreeNode *dcNode;

			if (GetLeftSubTree(dNode) != NULL)
				dcNode = GetLeftSubTree(dNode);
			else
				dcNode = GetRightSubTree(dNode);

			if (GetLeftSubTree(pNode) == dNode)
				ChangeLeftSubTree(pNode, dcNode);
			else
				ChangeRightSubTree(pNode, dcNode);
		}
		else {
			BSTreeNode *mNode = GetRightSubTree(dNode);
			BSTreeNode *mpNode = dNode;
			int delData;

			while (GetLeftSubTree(mNode) != NULL){
				mpNode = mNode;
				mNode = GetLeftSubTree(mNode);
			}

			delData = GetData(dNode);
			SetData(dNode, GetData(mNode));
			if (GetLeftSubTree(mNode) == mNode)
				ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
			else
				ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

			dNode = mNode;
			SetData(dNode, delData);
		}

		if (GetRightSubTree(pVRoot) != *pRoot)
			*pRoot = GetRightSubTree(pVRoot);

		free(pVRoot);
		return dNode;
	}
	void BSTShowAll(BSTreeNode *bst);
};
void BSTREE::MakeLeftSubTree(BSTreeNode *main, BSTreeNode *sub){
	if (main->left != NULL)
		delete main->left;
	main->left = sub;
}
void BSTREE::MakeRightSubTree(BSTreeNode *main, BSTreeNode *sub){
	if (main->right != NULL)
		delete main->right;
	main->right = sub;
}
void BSTREE::InorderTraverse(BSTreeNode *bst, VisitFuncPtr action){
	if (bst == NULL){
		return;
	}
	InorderTraverse(bst->left,action);
	action(bst->data);
	InorderTraverse(bst->right,action);
}
void BSTREE::BSTInsert(BSTreeNode **pRoot, BSTData data){
	BSTreeNode *pNode = NULL;
	BSTreeNode *cNode = *pRoot;
	BSTreeNode *nNode = NULL;

	while (cNode != NULL){
		if (data == GetData(cNode))
			return;

		pNode = cNode;

		if (GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

		nNode = MakeBSTreeNode();
		SetData(nNode, data);

		if (pNode != NULL){
			if (data < GetData(pNode))
				MakeLeftSubTree(pNode, nNode);
			else
				MakeRightSubTree(pNode, nNode);
		}
		else
			*pRoot = nNode;
}
void showData(int data){ cout << " " << data; }
void BSTREE::BSTShowAll(BSTreeNode *bst){
	InorderTraverse(bst, showData);
}