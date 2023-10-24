#ifndef QUEUE
#define QUEUE

#include<stdio.h>
#include<stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;

struct Node {
	int data;
	Node* previous;
};

struct Queue {
	Node* front;	//���V�e��
	Node* rear;		//���V����

	int nowElementNum;	//�{�b�s�񪺤����ƶq
};

//���Xqueue front���`�I
Node* Delete(Queue*);
//���J�`�I��queue rear
void Add(Queue*, Node*);
//�ˬd��e��queue�O�_���� �O�^��1 �_�^��0
int IsEmpty(Queue*);

//�`�I���غc�l �Ѻc�l
Node* NodeNew(int);
void FreeNode(Node*);

Queue* QueueNew();

int main() {

	Queue* q = QueueNew();

	for (int i = 0; i < 5; i++) {
		Add(q, NodeNew(i));
	}

	for (int i = 0; i < 5; i++) {
		Node* p = Delete(q);
		printf("%d\n", p->data);
		FreeNode(p);
	}

	return 0;
}

Node* Delete(Queue* q) {
	//�p�G���C�D��
	if (IsEmpty(q) == 0) {
		Node* p = q->front;		//������e���C�̫e�誺�`�I

		if(p != NULL) q->front = p->previous;		//�N�{�b���C���̫e��אּ���Y�����W�@�ӤH
		q->nowElementNum--;

		return p;
	}
	else {
		return NULL;
	}
}

int IsEmpty(Queue* q) {
	if (q->nowElementNum == 0) return 1;	//�Ū� �^��1
	else return 0;
}

void Add(Queue* q, Node* n) {
	if (n == NULL) return;

	Node* p = q->rear;	//�N��e�����ڸ`�I�O���U��

	if(p != NULL) p->previous = n;	//�Np���W�@���I�]�m���s���`�In
	q->rear = n;	//�N���ڼаO�]�m���s���`�In
	if (q->nowElementNum == 0) q->front = q->rear;	//�p�G�O�[�J�Ĥ@�Ӹ`�I ��l��front
	
	n->previous = NULL;	//����̫᭱���᭱�ONULL

	q->nowElementNum++;		//�Nq���������p�q+1
}

Node* NodeNew(int data) {
	Node* n = (Node*)malloc(sizeof(Node));	//���t�O����Ŷ���Node

	n->data = data;
	n->previous = NULL;

	return n;
}

void FreeNode(Node* n) {
	free(n);
}

Queue* QueueNew() {
	Queue* q = (Queue*)malloc(sizeof(Queue));

	q->nowElementNum = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}

#endif