#include<stdio.h>
#include<stdlib.h>

typedef struct Node* treePointer;	//�`�I���w
typedef struct Node {
	char data;
	treePointer leftChild, rightChild;	//���k�l�`�I
} node; //�`�I
typedef struct BinaryTree {
	treePointer root;
} binaryTree;	 //��

//Queue
//���w
typedef struct QNode* nodePointer;
typedef struct Queue* queuePointer;

//����
typedef struct QNode {
	treePointer tp;
	nodePointer previous;
} QNode;
typedef struct Queue {
	nodePointer front;	//���V�e��
	nodePointer rear;		//���V����

	int nowElementNum;	//�{�b�s�񪺤����ƶq
} Queue;

void PreorderTraversal(const binaryTree);
void RecurPreorder(const treePointer);

int FindHeight(const binaryTree);
int RecurHeight(const treePointer);

//���𪺸`�I�� ��k�P�W ���j�֥[���k�l�ƪ��`�I��
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

//�e�ǹM��
void PreorderTraversal(const binaryTree tree) {
	if(tree.root != NULL) RecurPreorder(tree.root);	//�p�G�𤣬O�Ū� �}�l�M��
}

//�e�ǹM�������j�϶�
void RecurPreorder(const treePointer tp) {
	//�p�G�o�Ӹ`�I�D��
	if (tp != NULL) {
		printf("%c", tp->data);
		RecurPreorder(tp->leftChild);
		RecurPreorder(tp->rightChild);
	}
}

//��o�𪺰���
int FindHeight(const binaryTree tree) {
	if (tree.root != NULL) return RecurHeight(tree.root);	//�s�b���� >0
	else return -1;		//�ž�A���s�b����
}

//�𪺰��ת����j�϶�
int RecurHeight(const treePointer tp) {
	//�p�G�o�Ӹ`�I�D��
	if (tp != NULL) {
		//printf("%c", tp->data);
		return Max(RecurHeight(tp->leftChild), RecurHeight(tp->rightChild)) + 1;
	}
	else {
		return 0;	//�N����leaf node���~���A���׬�0
	}
}

//Max Function
int Max(int a, int b) {
	if (a > b) return a;
	else return b;
}

//���J�`�I �Ͼ𬰤@�ӧ����
void InsertComplete(binaryTree* tree, char data) {
	//�s�`�I��l��
	treePointer tp = (treePointer)malloc(sizeof(node));
	tp->data = data;
	tp->leftChild = tp->rightChild = NULL;
	
	if (tree->root == NULL) {
		tree->root = tp;
	}
	else {
		Queue* queue = QueueNew();

		Add(queue, NodeNew(tree->root));	//���[�J�ڸ`�I

		/* ��queue���J�C�@�Ӹ`�I�A�p�G�o�Ӹ`�I�����Υk�l�`�I�ONULL�A�h�s�`�I�K�[�b��
		* �_�h�N���k�l�`�I�A��iqueue��
		* ����Y�OBFS
		*/
		while (IsEmpty(queue) == 0)
		{
			QNode* qn = Delete(queue);	//�����X�@�Ӹ`�I

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
				Add(queue, NodeNew(qn->tp->leftChild));	//�[�J���`�I
				Add(queue, NodeNew(qn->tp->rightChild));	//�[�J�k�`�I
			}
		}
	}
}

//���Xqueue front���`�I
nodePointer Delete(queuePointer q) {
	//�p�G���C�D��
	if (IsEmpty(q) == 0) {
		nodePointer p = q->front;		//������e���C�̫e�誺�`�I

		if (p != NULL) q->front = p->previous;		//�N�{�b���C���̫e��אּ���Y�����W�@�ӤH
		q->nowElementNum--;

		return p;
	}
	else {
		return NULL;
	}
}

//�ˬd��e��queue�O�_���� �O�^��1 �_�^��0
int IsEmpty(queuePointer q) {
	if (q->nowElementNum == 0) return 1;	//�Ū� �^��1
	else return 0;
}

//���J�`�I��queue rear
void Add(queuePointer q, nodePointer n) {
	if (n == NULL) return;

	nodePointer p = q->rear;	//�N��e�����ڸ`�I�O���U��

	if (p != NULL) p->previous = n;	//�Np���W�@���I�]�m���s���`�In
	q->rear = n;	//�N���ڼаO�]�m���s���`�In
	if (q->nowElementNum == 0) q->front = q->rear;	//�p�G�O�[�J�Ĥ@�Ӹ`�I ��l��front

	n->previous = NULL;	//����̫᭱���᭱�ONULL

	q->nowElementNum++;		//�Nq���������p�q+1
}

//�`�I���غc�l
nodePointer NodeNew(treePointer tp) {
	nodePointer n = (nodePointer)malloc(sizeof(QNode));	//���t�O����Ŷ���Node

	n->tp = tp;
	n->previous = NULL;

	return n;
}

//�`�I���Ѻc�l
void FreeNode(nodePointer n) {
	free(n);
}

//Queue���غc�l
queuePointer QueueNew() {
	queuePointer q = (queuePointer)malloc(sizeof(Queue));

	q->nowElementNum = 0;
	q->front = NULL;
	q->rear = NULL;

	return q;
}