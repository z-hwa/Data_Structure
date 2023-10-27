#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
	int data;
	Node* next;
};

struct Stack {
	Node* top;	//指向頂部
};

//推出stack頂部的節點
int Pop(Stack*);
//推入節點到stack頂部
void Push(Stack*, Node*);
//檢查當前的stack是否為空 是回傳1 否回傳0
int IsEmpty(Stack*);
//回傳當前stack頂部的節點
Node* Top(Stack*);

//節點的建構子
Node* NodeNew(int);

int main() {

	Stack* s = (Stack*)malloc(sizeof(Stack));

	for (int i = 0; i < 5; i++) {
		Push(s, NodeNew(i));
	}

	for (int i = 0; i < 5; i++) {
		printf("%d\n", Top(s)->data);
		Pop(s);
	}

	return 0;
}

int Pop(Stack* s) {
	if (IsEmpty(s) == 0) {
		Node* p = s->top;

		s->top = p->next;	//將頭部移除

		free(p);	//釋放記憶體
		return 1;
	}
	else {
		return 0;
	}
}

int IsEmpty(Stack* s) {
	if (s->top == NULL) return 1;	//空的 回傳1
	else return 0;
}

void Push(Stack* s, Node* n) {
	Node* p = s->top;

	s->top = n;	//改變頭部
	n->next = p;	//將新增設的節點 下一個點設為原本的頭部
}

Node* NodeNew(int data) {
	Node* n = (Node*)malloc(sizeof(Node));	//分配記憶體空間給Node

	n->data = data;
	n->next = NULL;

	return n;
}

Node* Top(Stack* s) {
	if (IsEmpty(s) == 0)
	{
		return s->top;
	}
	else {
		return NULL;
	}
}