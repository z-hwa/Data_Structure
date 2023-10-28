#include<stdio.h>
#include<stdlib.h>

typedef struct Node* treePointer;	//節點指針
typedef struct Node {
	int key;
	//int value;
	treePointer leftChild, rightChild;
} node;  //節點

typedef struct BinarySearchTree {
	treePointer root;
}BST;   //二元搜尋樹

void Insert(BST*, const treePointer);
treePointer NewTreePointer(const int);
void Delete(BST* bst, const int key);

//traversal the binary search tree
void PreorderTraversal(const BST);
void RecurPreorder(const treePointer);

int main() {

	BST* bst = (BST*)malloc(sizeof(BST));

	for (int i = 0; i < 5; i++) {
		treePointer tp = NewTreePointer(i);	//create new tree node

		Insert(bst, tp);	//put into binary search tree
	}

	PreorderTraversal(*bst);
	Delete(bst, 0);
	PreorderTraversal(*bst);

	return 0;
}

//插入一個節點(假設key不重複
void Insert(BST* bst, const treePointer newNode) {
	//如果樹是空的 直接插入在根節點
	if (bst->root == NULL) {
		bst->root = newNode;
	}
	else {
		int key = newNode->key;	//取得key
		treePointer tp = bst->root;	//新增指針指向根節點

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
treePointer NewTreePointer(const int key) {
	treePointer tp = (treePointer)malloc(sizeof(node));
	tp->key = key;
	tp->leftChild = NULL;
	tp->rightChild = NULL;

	return tp;
}

//Delete node by key from binary search tree
void Delete(BST* bst, const int key) {
	//this binary search tree is empty
	if (bst->root == NULL) return;
	
	treePointer p = bst->root;	//create a pointer 'p' pointed to root of tree
	treePointer parentP = NULL;	//trace parent of p

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

		free(p);
	}
	else if (p->leftChild != NULL && p->rightChild == NULL) {
		//a 1-degree node
		treePointer childOfP = p->leftChild;	//trace child of p

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = childOfP;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = childOfP;
		else if (parentP == NULL) {
			bst->root = childOfP;
		}
	}
	else if (p->leftChild == NULL && p->rightChild != NULL) {
		//a 1-degree node
		treePointer childOfP = p->rightChild;	//trace child of p

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

		treePointer maxIn_LeftChild = p->leftChild;
		while (maxIn_LeftChild->rightChild != NULL) {
			maxIn_LeftChild = maxIn_LeftChild->rightChild;	//持續找右邊的子節點
		}

		//RecordData of the chlld
		int childKey = maxIn_LeftChild->key;

		Delete(bst, childKey);	//delete child
		
		//set data of p as the child
		p->key = childKey;
	}

	return;
}

//前序遍歷
void PreorderTraversal(const BST tree) {
	if (tree.root != NULL) RecurPreorder(tree.root);	//如果樹不是空的 開始遍歷
}

//前序遍歷的遞迴區塊
void RecurPreorder(const treePointer tp) {
	//如果這個節點非空
	if (tp != NULL) {
		printf("%d", tp->key);
		RecurPreorder(tp->leftChild);
		RecurPreorder(tp->rightChild);
	}
}