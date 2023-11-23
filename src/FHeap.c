#include<stdio.h>

typedef long long lld;

typedef struct FNode* F_nodeP;
typedef struct FNode {
	F_nodeP child;	//point to one of this node's child
					//null iff no child
	F_nodeP leftS, rightS;	//point to sibling of this child
	F_nodeP parent;	//papa
	bool childCut;	//record event of delete child

	//data
	int key;
	int value;
}FNode;	//節點原型

typedef struct FHeap* F_heapP;
typedef struct FHeap {
	F_nodeP root;
} FHeap;  //Fheap原型

F_nodeP CreateNode(const lld key, const lld value);
void Insert(F_heapP heap, const lld key, const lld value);
void PutNodeInCir(F_nodeP root, F_nodeP newNode);

int main() {



	return 0;
}

//insert node into Fheap
void Insert(F_heapP heap, const lld key, const lld value) {
	//create node which want to insert
	F_nodeP newNode = CreateNode(key, value);

	F_nodeP root = heap->root;	//get pointer of root(min key

	if (root == NULL) {
		//this is a empty FHeap
		heap->root = newNode;	//set root as new node
	}
	else if (root->key > newNode->key) {
		//new node's key smaller than root
		//insert newnode as root

		PutNodeInCir(root, newNode);	//put node in circular

		//set root
		heap->root = newNode;
	}
	else {
		PutNodeInCir(root, newNode);	//put node in circular
	}
}

//put newNode in circular list which root inside
void PutNodeInCir(F_nodeP root, F_nodeP newNode) {
	F_nodeP right, left;

	//insert new node at root's left
	left = root->leftS;
	right = root->rightS;

	//put new node at left side of root
	if (left != NULL) {
		root->leftS = newNode;
		newNode->rightS = root;

		newNode->leftS = left;
		left->rightS = newNode;
	}
	else if (right != NULL) {
		root->rightS = newNode;
		newNode->leftS = root;

		newNode->rightS = right;
		right->leftS = newNode;
	}
	else {
		//if no sibling of this root put in
		root->leftS = newNode;
		newNode->rightS = root;

		newNode->leftS = root;
		root->rightS = newNode;
	}
}

//create default node by key and value
F_nodeP CreateNode(const lld key, const lld value) {
	F_nodeP newNode = (F_nodeP)malloc(sizeof(FNode));	//allocate new node address

	//struct part
	newNode->child = NULL;
	newNode->leftS = newNode->rightS = NULL;
	newNode->parent = NULL;
	newNode->childCut = false;

	//data part
	newNode->key = key;
	newNode->value = value;

	return newNode;	//return node
}