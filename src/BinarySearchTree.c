#include<stdio.h>
#include<stdlib.h>

typedef struct Node* treePointer;	//�`�I���w
typedef struct Node {
	int key;
	//int value;
	treePointer leftChild, rightChild;
} node;  //�`�I

typedef struct BinarySearchTree {
	treePointer root;
}BST;   //�G���j�M��

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

//���J�@�Ӹ`�I(���]key������
void Insert(BST* bst, const treePointer newNode) {
	//�p�G��O�Ū� �������J�b�ڸ`�I
	if (bst->root == NULL) {
		bst->root = newNode;
	}
	else {
		int key = newNode->key;	//���okey
		treePointer tp = bst->root;	//�s�W���w���V�ڸ`�I

		//�V�U�}�l��
		while (tp != NULL)
		{
			//�skey�j���e�`�I��key
			if (key > tp->key) {

				//�k�`�I���� �N�s�`�I�[�b����
				//�D�� ���w�V�k�`�I����
				if (tp->rightChild == NULL) {
					tp->rightChild = newNode;
					break;
				}
				else {
					tp = tp->rightChild;
				}
			}else if (key < tp->key) {

				//���`�I���� �N�s�`�I�[�b����
				//�D�� ���w�V���`�I����
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

//�^�Ǥ@�ӷs����`�I
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
			maxIn_LeftChild = maxIn_LeftChild->rightChild;	//�����k�䪺�l�`�I
		}

		//RecordData of the chlld
		int childKey = maxIn_LeftChild->key;

		Delete(bst, childKey);	//delete child
		
		//set data of p as the child
		p->key = childKey;
	}

	return;
}

//�e�ǹM��
void PreorderTraversal(const BST tree) {
	if (tree.root != NULL) RecurPreorder(tree.root);	//�p�G�𤣬O�Ū� �}�l�M��
}

//�e�ǹM�������j�϶�
void RecurPreorder(const treePointer tp) {
	//�p�G�o�Ӹ`�I�D��
	if (tp != NULL) {
		printf("%d", tp->key);
		RecurPreorder(tp->leftChild);
		RecurPreorder(tp->rightChild);
	}
}