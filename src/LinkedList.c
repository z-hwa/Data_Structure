#ifndef LINKEDLIST
#define LINKEDLIST

#include<stdio.h>
#include<stdlib.h>

typedef struct listNode* listPointer;	//節點指針
typedef struct listNode{
	char data;
	listPointer link;
} listNode; //節點
typedef struct linkedList{
	listPointer first;
} linkedList;	 //連結串列結構

listPointer Get(const linkedList, const int);	//取得第k個節點
int IsEmpty(const linkedList);	//檢查linked list非空
int Delete(linkedList*, const char);	//根據char 刪除資料(成功回傳1 失敗回傳0
int Insert(linkedList*, const char, const char);	//插入資料到特定節點前 若目的地為空字元，則為插入到頭部

//linked list初始化
linkedList ll;

int main() {

	return 0;
}

listPointer Get(const linkedList ll, const int id) {
	if (IsEmpty(ll) == 1) return NULL;	//連結串列為空

	listPointer p = ll.first;

	int i = 0;
	for (; i < id; i++) {
		if (p == NULL) break;	//避免非法讀取
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
	if (IsEmpty(*ll) == 1) return 0;	//空鏈結串列
	
	listPointer p = ll->first;

	//如果第一個就是想刪除的元素
	if (p->data == data) {
		ll->first = NULL;
		free(p);

		return 1;
	}
	else {
		//第一個不是的話
		//p非空(避免非法讀取
		//p移動到 想要刪除的節點 的前一個節點
		while (p != NULL && p->link->data != data) {
			p = p->link;	//向前移動
		}

		//找不到對應的資料 刪除失敗
		if (p == NULL) return 0;

		listPointer deleteNode = p->link;	//紀錄準備被刪除的節點
		p->link = p->link->link;	//跳過被刪除節點

		free(deleteNode);	//釋放節點

		return 1;
	}
}

int Insert(linkedList* ll, const char data, const char target) {
	listPointer lp = ll->first;	//用lp指向當前的第一個節點
	
	//初始化插入節點
	listPointer newNode = (listPointer)malloc(sizeof(listNode));
	newNode->data = data;
	
	//插入到頭部
	if (target == ' ')
	{
		newNode->link = lp;	//將新節點的link設為原頭部

		ll->first = newNode;	//更新連結串列的第一個節點
		return 1;
	}
	else {
		if (IsEmpty(*ll) == 1) return 0;	//空連結串列

		listPointer p = ll->first;

		//p非空(避免非法讀取
		//p移動到 目標節點 的前一個節點
		while (p != NULL && p->link->data != target) {
			p = p->link;	//向前移動
		}

		//找不到對應的資料 插入失敗
		if (p == NULL) return 0;

		newNode->link = p->link;	//將新節點的連結 指向目標點
		p->link = newNode;	//將目標點前一個節點的link指向新節點

		return 1;
	}
}

#endif