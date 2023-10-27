#include<stdio.h>
#include<stdlib.h>

//指針
typedef struct Node* nodePointer;
typedef struct Queue* queuePointer;

//本體
typedef struct Node {
	int data;
	nodePointer previous;
} Node;
typedef struct Queue {
	nodePointer front;	//指向前方
	nodePointer rear;		//指向尾巴

	int nowElementNum;	//現在存放的元素數量
} Queue;

//推出queue front的節點
nodePointer Delete(queuePointer);
//推入節點到queue rear
void Add(queuePointer, nodePointer);
//檢查當前的queue是否為空 是回傳1 否回傳0
int IsEmpty(queuePointer);

//節點的建構子 解構子
nodePointer NodeNew(int);
void FreeNode(nodePointer);

//Queue的建構子
queuePointer QueueNew();

int main() {

	queuePointer q = QueueNew();

	for (int i = 0; i < 5; i++) {
		Add(q, NodeNew(i));
	}

	for (int i = 0; i < 5; i++) {
		nodePointer p = Delete(q);
		printf("%d\n", p->data);
		FreeNode(p);
	}

	return 0;
}

nodePointer Delete(queuePointer q) {
	//如果隊列非空
	if (IsEmpty(q) == 0) {
		nodePointer p = q->front;		//紀錄當前隊列最前方的節點

		if(p != NULL) q->front = p->previous;		//將現在隊列的最前方改為原頭部的上一個人
		q->nowElementNum--;

		return p;
	}
	else {
		return NULL;
	}
}

int IsEmpty(queuePointer q) {
	if (q->nowElementNum == 0) return 1;	//空的 回傳1
	else return 0;
}

void Add(queuePointer q, nodePointer n) {
	if (n == NULL) return;

	nodePointer p = q->rear;	//將當前的尾巴節點記錄下來

	if(p != NULL) p->previous = n;	//將p的上一個點設置為新的節點n
	q->rear = n;	//將尾巴標記設置為新的節點n
	if (q->nowElementNum == 0) q->front = q->rear;	//如果是加入第一個節點 初始化front
	
	n->previous = NULL;	//隊伍最後面的後面是NULL

	q->nowElementNum++;		//將q中的元素計量+1
}

nodePointer NodeNew(int data) {
	nodePointer n = (nodePointer)malloc(sizeof(Node));	//分配記憶體空間給Node

	n->data = data;
	n->previous = NULL;

	return n;
}

void FreeNode(nodePointer n) {
	free(n);
}

queuePointer QueueNew() {
	queuePointer q = (queuePointer)malloc(sizeof(Queue));

	q->nowElementNum = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}