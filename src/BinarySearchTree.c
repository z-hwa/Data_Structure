#include<stdio.h>
#include<stdlib.h>

typedef long long lld;

typedef struct Node* TreePointer;	//節點指針
typedef struct Node {
	int key;
	//int value;
	TreePointer leftChild, rightChild;
} node;  //節點

typedef struct BinarySearchTree* BSTP;
typedef struct BinarySearchTree {
	TreePointer root;
}BST;   //二元搜尋樹

void Insert(BSTP bst, const TreePointer newNode);
TreePointer NewTreePointer(const lld);
void Delete(BSTP bst, const int key);
void CopyNode(TreePointer a, const TreePointer b);

//traversal the binary search tree
void PreorderTraversal(const BST);
void RecurPreorder(const TreePointer);

int main() {

	BST* bst = (BST*)malloc(sizeof(BST));

	for (int i = 0; i < 5; i++) {
		TreePointer tp = NewTreePointer(i);	//create new tree node

		Insert(bst, tp);	//put into binary search tree
	}

	PreorderTraversal(*bst);
	Delete(bst, 0);
	PreorderTraversal(*bst);

	return 0;
}

//插入一個節點(假設key不重複
void Insert(BSTP bst, const TreePointer newNode) {

	//如果樹是空的 直接插入在根節點
	if (bst->root == NULL) {
		bst->root = newNode;
	}
	else {
		lld key = newNode->key;
		TreePointer tp = bst->root;	//新增指針指向根節點

		//向下開始塞
		while (tp != NULL)
		{
			//新key大於當前節點的key
			if (key > tp->key) {

				//右節點為空 將新節點加在那裡
				//非空 指針向右節點移動
				if (tp->rightChild == NULL) {
					tp->rightChild = newNode;
					break;
				}
				else {
					tp = tp->rightChild;
				}
			}else if (key < tp->key) {

				//左節點為空 將新節點加在那裡
				//非空 指針向左節點移動
				if (tp->leftChild == NULL) {
					tp->leftChild = newNode;
					break;
				}
				else {
					tp = tp->leftChild;
				}
			}
		}
	}
}

//回傳一個新的樹節點
TreePointer NewTreePointer(const lld key) {
	TreePointer tp = (TreePointer)malloc(sizeof(node));
	tp->key = key;
	tp->leftChild = NULL;
	tp->rightChild = NULL;

	return tp;
}

//Delete node by key from binary search tree
void Delete(BSTP bst, const int key) {
	//this binary search tree is empty
	if (bst->root == NULL) return;
	
	TreePointer p = bst->root;	//create a pointer 'p' pointed to root of tree
	TreePointer parentP = NULL;	//trace parent of p

	//if p is not empty pointer
	//and the node key which pointed by 'p' doesn't equal to key
	//keeping find
	while (p != NULL && p->key != key) {
		parentP = p;	//since p must go to child, we can record p now

		//acording to key, decide p go to the left child or right 
		if (key > p->key) {
			p = p->rightChild;
		}
		else if (key < p->key) {
			p = p->leftChild;
		}
	}


	if (p == NULL) {
		//do not find node with same key
		return;
	}
	else if (p->leftChild == NULL && p->rightChild == NULL) {
		//a leaf node

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = NULL;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = NULL;
		else if (parentP == NULL) {
			bst->root = NULL;
		}
	}
	else if (p->leftChild != NULL && p->rightChild == NULL) {
		//a 1-degree node
		TreePointer childOfP = p->leftChild;	//trace child of p

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = childOfP;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = childOfP;
		else if (parentP == NULL) {
			bst->root = childOfP;
		}
	}
	else if (p->leftChild == NULL && p->rightChild != NULL) {
		//a 1-degree node
		TreePointer childOfP = p->rightChild;	//trace child of p

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = childOfP;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = childOfP;
		else if (parentP == NULL) {
			bst->root = childOfP;
		}
	}
	else if (p->leftChild != NULL && p->rightChild != NULL) {
		//2-degree node
		//replace p node by max key in left child
		//next, delete the child(which must be 0 or 1 degree node

		TreePointer maxIn_LeftChild = p->leftChild;
		while (maxIn_LeftChild->rightChild != NULL) {
			maxIn_LeftChild = maxIn_LeftChild->rightChild;	//持續找右邊的子節點
		}

		//RecordData of the chlld
		TreePointer temp = (TreePointer)malloc(sizeof(node));
		CopyNode(temp, maxIn_LeftChild);

		Delete(bst, maxIn_LeftChild->key);	//delete child
		
		//set data of p as the child
		CopyNode(p, temp);

		return;
	}

	free(p);
	return;
}

//copy function of node
void CopyNode(TreePointer a, const TreePointer b) {
	a->key = b->key;
	return;
}

//前序遍歷
void PreorderTraversal(const BST tree) {
	if (tree.root != NULL) RecurPreorder(tree.root);	//如果樹不是空的 開始遍歷
}

//前序遍歷的遞迴區塊
void RecurPreorder(const TreePointer tp) {
	//如果這個節點非空
	if (tp != NULL) {
		printf("%d", tp->key);
		RecurPreorder(tp->leftChild);
		RecurPreorder(tp->rightChild);
	}
}