#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
}Node;

typedef struct Heap {
	Node* root;	//���V����node���Ʋ�

	int maxNum;	//�����j�p
	int nowElementNum;	//������e�������Ӽ�
}Heap;

Heap* CreateHeap(int n);
void Insert(Heap* h, Node newNode);
void NodeSwap(Heap* h, const int a, const int b);

int main() {

	Heap* h = CreateHeap(5);
	for (int i = 0; i < 5; i++) {
		Node n;
		n.data = i;
		Insert(h, n);
	}

	return 0;
}

//�Ыؤ@��heap
Heap* CreateHeap(int n) {

	Heap* h = (Heap*)malloc(sizeof(Heap));	//point to heap's pointer
	h->root = (Node*)malloc(sizeof(Node) * n);	//pointer which pointed to data space

	h->maxNum = n;	//�]�w�̤j�W��
	h->nowElementNum = 0;	//�]�w��e�������Ӽ�

	return h;
}

void Insert(Heap* h, Node newNode) {
	if (h->nowElementNum >= h->maxNum) return;	//the heap is full, can not insert

	Node* heapList = h->root;	//create a pointer pointed to root
	int count = h->nowElementNum;	//get now elements number

	heapList[++count] = newNode;	//add node at heap's end

	h->nowElementNum = count;	//update now element #

	int i = count;	//index to data
	while ((i / 2) > 0 && heapList[i].data > heapList[i/2].data) {
		NodeSwap(h, i, i/2);
		i /= 2;
	}
}

//�洫�`�I
void NodeSwap(Heap* h, const int a, const int b) {
	Node* heapList = h->root;	//create a pointer pointed to root

	Node temp = heapList[a];
	heapList[a] = heapList[b];
	heapList[b] = temp;
}
