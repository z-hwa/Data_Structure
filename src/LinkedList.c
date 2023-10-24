#include<stdio.h>

typedef struct listNode* listPointer;	//節點指針
typedef struct listNode{
	char data;
	listPointer link;
} listNode; //節點本體

listPointer Get(listPointer, int);	//取得第k個節點
int IsEmpty(listPointer);	//檢查linked list非空

//linked list初始化
listPointer first = NULL;

int main() {
	return 0;
}

listPointer Get(const listPointer lp, const int id) {
	
	listPointer p = lp;

	int i = 0;
	for (; i < id; i++) {
		if (IsEmpty(p) == 1) break;	//避免非法讀取
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