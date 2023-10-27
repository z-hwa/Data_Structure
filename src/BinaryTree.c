#include<stdio.h>
#include<stdlib.h>

typedef struct Node* treePointer;	//節點指針
typedef struct Node {
	char data;
	treePointer leftChild, rightChild;	//左右子節點
} node; //節點
typedef struct BinaryTree {
	treePointer root;
} binaryTree;	 //樹

//Queue
//指針
typedef struct QNode* nodePointer;
typedef struct Queue* queuePointer;

//本體
typedef struct QNode {
	treePointer tp;
	nodePointer previous;
} QNode;
typedef struct Queue {
	nodePointer front;	//指向前方
	nodePointer rear;		//指向尾巴

	int nowElementNum;	//現在存放的元素數量
} Queue;

void PreorderTraversal(const binaryTree);
void RecurPreorder(const treePointer);

int FindHeight(const binaryTree);
int RecurHeight(const treePointer);

//找到樹的節點數 方法同上 遞迴累加左右子數的節點數
//int FindNodeNum(const binaryTree);
//int RecurNodeNum(const binaryTree);

void InsertComplete(binaryTree*, char);

int Max(int a, int b);

//QUEUE
nodePointer Delete(queuePointer);
void Add(queuePointer, nodePointer);
int IsEmpty(queuePointer);

nodePointer NodeNew(treePointer);
void FreeNode(nodePointer);

queuePointer QueueNew();

int main() {

	binaryTree bt;
	bt.root = NULL;

	InsertComplete(&bt, 'a');
	InsertComplete(&bt, 'b');
	InsertComplete(&bt, 'c');
	InsertComplete(&bt, 'd');
	InsertComplete(&bt, 'e');

	PreorderTraversal(bt);

	return 0;
}

//前序遍歷
void PreorderTraversal(const binaryTree tree) {
	if(tree.root != NULL) RecurPreorder(tree.root);	//如果樹不是空的 開始遍歷
}

//前序遍歷的遞迴區塊
void RecurPreorder(const treePointer tp) {
	//如果這個節點非空
	if (tp != NULL) {
		printf("%c", tp->data);
		RecurPreorder(tp->leftChild);
		RecurPreorder(tp->rightChild);
	}
}

//獲得樹的高度
int FindHeight(const binaryTree tree) {
	if (tree.root != NULL) return RecurHeight(tree.root);	//存在高度 >0
	else return -1;		//空樹，不存在高度
}

//樹的高度的遞迴區塊
int RecurHeight(const treePointer tp) {
	//如果這個節點非空
	if (tp != NULL) {
		//printf("%c", tp->data);
		return Max(RecurHeight(tp->leftChild), RecurHeight(tp->rightChild)) + 1;
	}
	else {
		return 0;	//代表走到leaf node的外面，高度為0
	}
}

//Max Function
int Max(int a, int b) {
	if (a > b) return a;
	else return b;
}

//插入節點 使樹為一個完整樹
void InsertComplete(binaryTree* tree, char data) {
	//新節點初始化
	treePointer tp = (treePointer)malloc(sizeof(node));
	tp->data = data;
	tp->leftChild = tp->rightChild = NULL;
	
	if (tree->root == NULL) {
		tree->root = tp;
	}
	else {
		Queue* queue = QueueNew();

		Add(queue, NodeNew(tree->root));	//先加入根節點

		/* 用queue載入每一個節點，如果這個節點的左或右子節點是NULL，則新節點添加在那
		* 否則將左右子節點，放進queue中
		* 思路即是BFS
		*/
		while (IsEmpty(queue) == 0)
		{
			QNode* qn = Delete(queue);	//先取出一個節點

			if (qn->tp->leftChild == NULL) {
				qn->tp->leftChild = tp;
				FreeNode(qn);

				free(queue);
				break;
			}
			else if (qn->tp->rightChild == NULL) {
				qn->tp->rightChild = tp;
				FreeNode(qn);

				free(queue);
				break;
			}
			else {
				Add(queue, NodeNew(qn->tp->leftChild));	//加入左節點
				Add(queue, NodeNew(qn->tp->rightChild));	//加入右節點
			}
		}
	}
}

//推出queue front的節點
nodePointer Delete(queuePointer q) {
	//如果隊列非空
	if (IsEmpty(q) == 0) {
		nodePointer p = q->front;		//紀錄當前隊列最前方的節點

		if (p != NULL) q->front = p->previous;		//將現在隊列的最前方改為原頭部的上一個人
		q->nowElementNum--;

		return p;
	}
	else {
		return NULL;
	}
}

//檢查當前的queue是否為空 是回傳1 否回傳0
int IsEmpty(queuePointer q) {
	if (q->nowElementNum == 0) return 1;	//空的 回傳1
	else return 0;
}

//推入節點到queue rear
void Add(queuePointer q, nodePointer n) {
	if (n == NULL) return;

	nodePointer p = q->rear;	//將當前的尾巴節點記錄下來

	if (p != NULL) p->previous = n;	//將p的上一個點設置為新的節點n
	q->rear = n;	//將尾巴標記設置為新的節點n
	if (q->nowElementNum == 0) q->front = q->rear;	//如果是加入第一個節點 初始化front

	n->previous = NULL;	//隊伍最後面的後面是NULL

	q->nowElementNum++;		//將q中的元素計量+1
}

//節點的建構子
nodePointer NodeNew(treePointer tp) {
	nodePointer n = (nodePointer)malloc(sizeof(QNode));	//分配記憶體空間給Node

	n->tp = tp;
	n->previous = NULL;

	return n;
}

//節點的解構子
void FreeNode(nodePointer n) {
	free(n);
}

//Queue的建構子
queuePointer QueueNew() {
	queuePointer q = (queuePointer)malloc(sizeof(Queue));

	q->nowElementNum = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}