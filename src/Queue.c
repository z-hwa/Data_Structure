#include<stdio.h>
#include<stdlib.h>

//���w
typedef struct Node* nodePointer;
typedef struct Queue* queuePointer;

//����
typedef struct Node {
	int data;
	nodePointer previous;
} Node;
typedef struct Queue {
	nodePointer front;	//���V�e��
	nodePointer rear;		//���V����

	int nowElementNum;	//�{�b�s�񪺤����ƶq
} Queue;

//���Xqueue front���`�I
nodePointer Delete(queuePointer);
//���J�`�I��queue rear
void Add(queuePointer, nodePointer);
//�ˬd��e��queue�O�_���� �O�^��1 �_�^��0
int IsEmpty(queuePointer);

//�`�I���غc�l �Ѻc�l
nodePointer NodeNew(int);
void FreeNode(nodePointer);

//Queue���غc�l
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
	//�p�G���C�D��
	if (IsEmpty(q) == 0) {
		nodePointer p = q->front;		//������e���C�̫e�誺�`�I

		if(p != NULL) q->front = p->previous;		//�N�{�b���C���̫e��אּ���Y�����W�@�ӤH
		q->nowElementNum--;

		return p;
	}
	else {
		return NULL;
	}
}

int IsEmpty(queuePointer q) {
	if (q->nowElementNum == 0) return 1;	//�Ū� �^��1
	else return 0;
}

void Add(queuePointer q, nodePointer n) {
	if (n == NULL) return;

	nodePointer p = q->rear;	//�N��e�����ڸ`�I�O���U��

	if(p != NULL) p->previous = n;	//�Np���W�@���I�]�m���s���`�In
	q->rear = n;	//�N���ڼаO�]�m���s���`�In
	if (q->nowElementNum == 0) q->front = q->rear;	//�p�G�O�[�J�Ĥ@�Ӹ`�I ��l��front
	
	n->previous = NULL;	//����̫᭱���᭱�ONULL

	q->nowElementNum++;		//�Nq���������p�q+1
}

nodePointer NodeNew(int data) {
	nodePointer n = (nodePointer)malloc(sizeof(Node));	//���t�O����Ŷ���Node

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