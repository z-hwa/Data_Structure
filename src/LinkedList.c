#ifndef LINKEDLIST
#define LINKEDLIST

#include<stdio.h>
#include<stdlib.h>

typedef struct listNode* listPointer;	//�`�I���w
typedef struct listNode{
	char data;
	listPointer link;
} listNode; //�`�I
typedef struct linkedList{
	listPointer first;
} linkedList;	 //�s����C���c

listPointer Get(const linkedList, const int);	//���o��k�Ӹ`�I
int IsEmpty(const linkedList);	//�ˬdlinked list�D��
int Delete(linkedList*, const char);	//�ھ�char �R�����(���\�^��1 ���Ѧ^��0
int Insert(linkedList*, const char, const char);	//���J��ƨ�S�w�`�I�e �Y�ت��a���Ŧr���A�h�����J���Y��

//linked list��l��
linkedList ll;

int main() {

	return 0;
}

listPointer Get(const linkedList ll, const int id) {
	if (IsEmpty(ll) == 1) return NULL;	//�s����C����

	listPointer p = ll.first;

	int i = 0;
	for (; i < id; i++) {
		if (p == NULL) break;	//�קK�D�kŪ��
		p = p->link;
	}

	if (i == id) {
		return p;
	}
	else {
		return NULL;
	}
}

int IsEmpty(const linkedList ll) {
	if (ll.first != NULL) return 0;
	else return 1;
}

int Delete(linkedList* ll, const char data) {
	if (IsEmpty(*ll) == 1) return 0;	//���쵲��C
	
	listPointer p = ll->first;

	//�p�G�Ĥ@�ӴN�O�Q�R��������
	if (p->data == data) {
		ll->first = NULL;
		free(p);

		return 1;
	}
	else {
		//�Ĥ@�Ӥ��O����
		//p�D��(�קK�D�kŪ��
		//p���ʨ� �Q�n�R�����`�I ���e�@�Ӹ`�I
		while (p != NULL && p->link->data != data) {
			p = p->link;	//�V�e����
		}

		//�䤣���������� �R������
		if (p == NULL) return 0;

		listPointer deleteNode = p->link;	//�����ǳƳQ�R�����`�I
		p->link = p->link->link;	//���L�Q�R���`�I

		free(deleteNode);	//����`�I

		return 1;
	}
}

int Insert(linkedList* ll, const char data, const char target) {
	listPointer lp = ll->first;	//��lp���V��e���Ĥ@�Ӹ`�I
	
	//��l�ƴ��J�`�I
	listPointer newNode = (listPointer)malloc(sizeof(listNode));
	newNode->data = data;
	
	//���J���Y��
	if (target == ' ')
	{
		newNode->link = lp;	//�N�s�`�I��link�]�����Y��

		ll->first = newNode;	//��s�s����C���Ĥ@�Ӹ`�I
		return 1;
	}
	else {
		if (IsEmpty(*ll) == 1) return 0;	//�ųs����C

		listPointer p = ll->first;

		//p�D��(�קK�D�kŪ��
		//p���ʨ� �ؼи`�I ���e�@�Ӹ`�I
		while (p != NULL && p->link->data != target) {
			p = p->link;	//�V�e����
		}

		//�䤣���������� ���J����
		if (p == NULL) return 0;

		newNode->link = p->link;	//�N�s�`�I���s�� ���V�ؼ��I
		p->link = newNode;	//�N�ؼ��I�e�@�Ӹ`�I��link���V�s�`�I

		return 1;
	}
}

#endif