#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
}Node;

typedef struct Heap {
	Node* root;	//指向紀錄node的數組

	int maxNum;	//推的大小
	int nowElementNum;	//紀錄當前的元素個數
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

//創建一個heap
Heap* CreateHeap(int n) {

	Heap* h = (Heap*)malloc(sizeof(Heap));	//point to heap's pointer
	h->root = (Node*)malloc(sizeof(Node) * n);	//pointer which pointed to data space

	h->maxNum = n;	//設定最大上限
	h->nowElementNum = 0;	//設定當前的元素個數

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

//交換節點
void NodeSwap(Heap* h, const int a, const int b) {
	Node* heapList = h->root;	//create a pointer pointed to root

	Node temp = heapList[a];
	heapList[a] = heapList[b];
	heapList[b] = temp;
}
