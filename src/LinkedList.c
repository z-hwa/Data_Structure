#include<stdio.h>

typedef struct listNode* listPointer;	//�`�I���w
typedef struct listNode{
	char data;
	listPointer link;
} listNode; //�`�I����

listPointer Get(listPointer, int);	//���o��k�Ӹ`�I
int IsEmpty(listPointer);	//�ˬdlinked list�D��

//linked list��l��
listPointer first = NULL;

int main() {
	return 0;
}

listPointer Get(const listPointer lp, const int id) {
	
	listPointer p = lp;

	int i = 0;
	for (; i < id; i++) {
		if (IsEmpty(p) == 1) break;	//�קK�D�kŪ��
		p = p->link;
	}

	if (i == id) {
		return p;
	}
	else {
		return NULL;
	}
}

int IsEmpty(listPointer lp) {
	if (lp != NULL) return 0;
	else return 1;
}