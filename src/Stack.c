#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct Stack Stack;

struct Node {
	int data;
	Node* next;
};

struct Stack {
	Node* top;	//���V����
};

//���Xstack�������`�I
int Pop(Stack*);
//���J�`�I��stack����
void Push(Stack*, Node*);
//�ˬd��e��stack�O�_���� �O�^��1 �_�^��0
int IsEmpty(Stack*);
//�^�Ƿ�estack�������`�I
Node* Top(Stack*);

//�`�I���غc�l
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

		s->top = p->next;	//�N�Y������

		free(p);	//����O����
		return 1;
	}
	else {
		return 0;
	}
}

int IsEmpty(Stack* s) {
	if (s->top == NULL) return 1;	//�Ū� �^��1
	else return 0;
}

void Push(Stack* s, Node* n) {
	Node* p = s->top;

	s->top = n;	//�����Y��
	n->next = p;	//�N�s�W�]���`�I �U�@���I�]���쥻���Y��
}

Node* NodeNew(int data) {
	Node* n = (Node*)malloc(sizeof(Node));	//���t�O����Ŷ���Node

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