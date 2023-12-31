#include<stdio.h>
#include<stdlib.h>

typedef long long lld;

typedef struct FNode* F_nodeP;
typedef struct FNode {
	F_nodeP child;	//point to one of this node's child
					//null iff no child
	F_nodeP leftS, rightS;	//point to sibling of this child
	F_nodeP parent;	//papa
	int childCut;	//record event of delete child
	int treeType;	//record that using this node as root, what kind this tree is?

	//data
	lld key;
	lld value;
}FNode;	//節點原型

typedef struct Node* TreePointer;	//節點指針
typedef struct Node {
	lld key;
	lld value;
	F_nodeP pos;
	TreePointer leftChild, rightChild;
} node;  //節點

typedef struct BinarySearchTree* BSTP;
typedef struct BinarySearchTree {
	TreePointer root;
}BST;   //二元搜尋樹

typedef struct FHeap* F_heapP;
typedef struct FHeap {
	F_nodeP root;
	BSTP bst;	//bst tree used to search data from feap
} FHeap;  //Fheap原型

F_nodeP CreateNode(const lld key, const lld value);
F_nodeP Insert(F_heapP heap, const lld key, const lld value);
void PutNodeInCir(F_nodeP root, F_nodeP newNode);
F_heapP CreateFHeap();
F_nodeP Meld(F_nodeP a, F_nodeP b);
F_nodeP ReturnMinTree(const F_nodeP a);
void DeleteMin(F_heapP heap, int show);
void ShowTop(const F_heapP heap, const int n);
void ShowTopValue(const F_heapP heap, const int n);
void MoveFromLevelToTop(F_heapP heap, F_nodeP pointer, const int mode);
void CascadingCut(F_heapP heap, F_nodeP pointer);
void Delete(F_heapP heap, const lld key, const lld value);
void DecreaseKey(F_heapP heap, const lld key, const lld value, const lld newkey);

/*binary search tree*/

void InsertBST(BSTP bst, TreePointer newNode);
TreePointer NewTreePointer(const lld key, const lld value, const F_nodeP pointer);
void DeleteBST(BSTP bst, const lld key, const lld value);
void CopyNode(TreePointer a, const TreePointer b);
BSTP CreateBST();
TreePointer Search(BSTP bst, const lld key, const lld value);

void AddData(F_heapP heap, const lld key, const lld value);

int main() {

	F_heapP heap = CreateFHeap();

	AddData(heap, 1, 1);
	AddData(heap, 2, 2);
	AddData(heap, 3, 3);
	AddData(heap, 4, 4);

	ShowTop(heap, 5);

	DecreaseKey(heap, 4, 4, 0);

	ShowTop(heap, 5);	

	Delete(heap, 3, 3);

	ShowTop(heap, 5);

	return 0;
}

//final api for add data
void AddData(F_heapP heap, const lld key, const lld value) {
	BSTP bst = heap->bst;	//get bst tree from FHeap
	
	F_nodeP np = Insert(heap, key, value);
	TreePointer tp = NewTreePointer(key, value, np);
	InsertBST(bst, tp);

}

/*remove node from  its level
* mode 1 move tree includeroot
* mode 2 move subtree
*/
void MoveFromLevelToTop(F_heapP heap, F_nodeP pointer, const int mode) {
	F_nodeP parent = pointer->parent;	//used to chekc child's relation of parent
	F_nodeP child = pointer->child;

	//get sibling pointer of pointer
	F_nodeP leftS, rightS;
	leftS = pointer->leftS;
	rightS = pointer->rightS;

	//if pointer has sibling, move it out to circular list
	if (pointer != leftS) {
		//removed node from circular list
		leftS->rightS = rightS;
		rightS->leftS = leftS;
	}

	//reset pointer's relation of sibling
	pointer->leftS = pointer->rightS = pointer;

	//reset parent's relation of child
	if (parent != NULL && parent->child == pointer) {
		if (pointer == leftS) parent->child = leftS;	//reset parent's child
		else parent->child = NULL;	//set parent's child into null
	}

	if(mode == 1) heap->root = Meld(heap->root, pointer);	//merge remove tree to top-level
	else if(mode == 2 && child != NULL) heap->root = Meld(heap->root, child);	//move child of this node to top-level	
																				//will reset child's parent to NULL in ReturnMinTree()

	return;
}

void CascadingCut(F_heapP heap, F_nodeP pointer) {
	//pointer is parent of delete node
	F_nodeP parent = pointer->parent;	//get parent of pointer
	if (parent == NULL) return;	//already in top-level => do not need to cascading cut

	if (pointer->childCut == 0) {
		pointer->childCut = 1;
		return;
	}
	else {
		//need to move this tree which has "pointer" as root to top-level
		MoveFromLevelToTop(heap, pointer, 1);

		CascadingCut(heap, parent);	//tracing up
	}
}

/*final api for delete
delete node from fheap
*/
void Delete(F_heapP heap, const lld key, const lld value) {
	BSTP bst = heap->bst;	//get bst tree from FHeap
	
	TreePointer tp = Search(bst, key, value);	//get node from binary search tree;
	if (tp == NULL) return;

	F_nodeP root = heap->root;
	F_nodeP pointer = tp->pos;
	F_nodeP parent = pointer->parent;

	if(pointer == root) {
		DeleteMin(heap, 0);
		return ;	//delete done by DeleteMin
	}
	
	//the node is not root
	MoveFromLevelToTop(heap, pointer, 2);	//move subtree to top-level

	free(pointer);	//release address of pointer

	if(parent != NULL) CascadingCut(heap, parent);

	return;
}

//decrease key value of specify node
void DecreaseKey(F_heapP heap, const lld key, const lld value, const lld newkey) {
	BSTP bst = heap->bst;	//get bst tree from Fheap
	TreePointer tp = Search(bst, key, value);	//get node by key and value in bst tree
	
	if(tp == NULL) return;	//target node is not find

	F_nodeP root = heap->root;	//get pointer of root
	F_nodeP pointer = tp->pos;	//get pointer of F_nodeP type in TreePointer's node
	
	F_nodeP parent = pointer->parent;	//get parent of pointer

	if(pointer == root) {
		//target of decrease node is root of heap => only do decrease
		pointer->key = newkey;	//do decrease
	
		return; //end decrease
	}
	else if(parent == NULL) {
		//since pointer has no papa => node in top-level

		//no papa of this node
		pointer->key = newkey;	//do decrease
		
		//check if root's key is bigger than pointer => change heap's root pointer
		if(root->key > pointer->key) {
			heap->root = pointer;
		}
	
		return;	//end decrease
	}
	else {
		//has parent
		if(parent->key < newkey) {
			//newkey is still bigger than papa => just decrease
			pointer->key = newkey;
			return;
		}else {
			//newkey is smaller than parent
			//after decrease node
			//remove the node from its sibling
			pointer->key = newkey;

			MoveFromLevelToTop(heap, pointer, 1);	//move tree to top-level
		}
	}

	if (parent != NULL) CascadingCut(heap, parent);

	return;
}

//show top-level circular list
void ShowTop(const F_heapP heap, const int n) {
	F_nodeP pointer = heap->root;

	//left circle
	for (int i = 0; i < n; i++) {
		printf("%lld->", pointer->key);

		pointer = pointer->leftS;
	}

	printf("\n");

	//right circle
	pointer = heap->root;
	for (int i = 0; i < n; i++) {
		printf("%lld->", pointer->key);

		pointer = pointer->rightS;
	}

	printf("\n");
}

//show top-level circular list value
void ShowTopValue(const F_heapP heap, const int n) {
	F_nodeP pointer = heap->root;

	//left circle
	for (int i = 0; i < n; i++) {
		printf("%lld->", pointer->value);

		pointer = pointer->leftS;
	}

	printf("\n");

	//right circle
	pointer = heap->root;
	for (int i = 0; i < n; i++) {
		printf("%lld->", pointer->value);

		pointer = pointer->rightS;
	}

	printf("\n");
}

//merge b-tree which have same order in top-level order
void Consolidation(F_heapP heap) {

	F_nodeP root = heap->root;

	//empty heap => consolidation is done
	if (root == NULL) return;

	int maxDepth = root->treeType;	//max depth of top-level tree of heap
	F_nodeP pointer = root->leftS;	//use to find max tree depth;

	//find max depth
	while (pointer != root)
	{
		if (pointer->treeType > maxDepth) maxDepth = pointer->treeType;
		pointer = pointer->leftS;	//go to next node
	}

	/*real manipulate part*/

	F_nodeP* treeTable = (F_nodeP*)malloc(sizeof(F_nodeP)*maxDepth);	//tree table to record that if there are two tree with same type
	F_nodeP next;

	pointer = root;	//reset pointer

	//check for all tree under top-level order
	do {
		next = pointer->leftS;	//first record next node

		//get tree type of this tree
		int treeType = pointer->treeType;

		//check tree table
		if (treeTable[treeType] == NULL) {
			//until now there is no same order tree for treeType
			treeTable[treeType] = pointer;
		}
		else {
			//must to merge now tree into previous tree with same order
			F_nodeP previousTree = treeTable[treeType];	//previous tree
			pointer->childCut = 0;	//reset cascading

			//remove this tree from top-level order
			F_nodeP leftS, rightS;
			leftS = pointer->leftS;
			rightS = pointer->rightS;

			leftS->rightS = rightS;
			rightS->leftS = leftS;

			//reset now tree's root as a new tree
			pointer->leftS = pointer->rightS = pointer;
			pointer->parent = previousTree;	//set parent

			//combine into previous tree
			if (previousTree->treeType == 0) {
				//previous tree has no child
				previousTree->child = pointer;
			}
			else {
				//combine into child circular list
				F_nodeP child = previousTree->child;

				PutNodeInCir(child, pointer);
			}

			//update tree type
			previousTree->treeType += 1;
		}

		pointer = next;	//go to next node
	} while (pointer != root);
}

//delete min in FHeap
void DeleteMin(F_heapP heap, int show) {
	F_nodeP root = heap->root;

	if (root == NULL) {
		//this is empty heap => delete failure
		return;
	}
	else {
		
		//first maintain child of root
		F_nodeP leftS = root->leftS;
		F_nodeP rightS = root->rightS;
		F_nodeP child = root->child;

		if (leftS == root && child == NULL) {
			//this FHeap has only B_{0} B-tree
			heap->root = NULL;
		}
		else if (leftS == root && child != NULL) {
			//this FHeap has one B-Tree which large than B_{0}
			heap->root = root->child;
		}
		else if (leftS != root) {
			//this FHeap has more than 1 B-Tree

			//remove min tree(root) from top-level circular list
			leftS->rightS = rightS;
			rightS->leftS = leftS;
			
			//temporary reset FHeap pointer
			heap->root = leftS;

			//if original root has child
			//meld child circular list and now top-level circular list
			if (child != NULL) {
				heap->root = Meld(heap->root, child);
			}
			else {
				//renew min tree after delete min
				heap->root = ReturnMinTree(heap->root);
			}

		}

		if(show == 1) printf("%lld %lld\n", root->key, root->value);	//show min
		free(root);	//release address of root
	}

	Consolidation(heap);
}

/*combine 2 top-level circular lists
* will return min tree in top-level
*/
F_nodeP Meld(F_nodeP a, F_nodeP b) {
	F_nodeP aSibling, bSibling;

	//get both a and bs' sibling
	aSibling = a->leftS;
	bSibling = b->leftS;

	//link a, bs' circular lists
	a->leftS = b;
	b->leftS = a;

	aSibling->rightS = bSibling;
	bSibling->rightS = aSibling;

	return ReturnMinTree(a);
}

//renew min tree in top-level
F_nodeP ReturnMinTree(const F_nodeP a) {
	//return min-element pointer
	F_nodeP pointer = a->leftS;
	F_nodeP finalAns = a;

	//if pointer == a => there is a node in the circular list
	//find the min element in top-level circular list
	while (pointer != a)
	{
		//renew min element
		if (finalAns->key > pointer->key) {
			finalAns = pointer;
		}

		pointer->parent = NULL;	//top-level has no parent
		pointer = pointer->leftS;	//go to next node
	}

	return finalAns;
}

//insert node into Fheap
F_nodeP Insert(F_heapP heap, const lld key, const lld value) {
	//create node which want to insert
	F_nodeP newNode = CreateNode(key, value);

	F_nodeP root = heap->root;	//get pointer of root(min key

	if (root == NULL) {
		//this is a empty FHeap

		heap->root = newNode;	//set root as new node
	}
	else if (root->key > newNode->key) {
		//new node's key smaller than root
		//insert newnode as root

		PutNodeInCir(root, newNode);	//put node in circular

		//set root
		heap->root = newNode;
	}
	else {
		PutNodeInCir(root, newNode);	//put node in circular
	}

	return newNode;
}

//put newNode in circular list which root inside
void PutNodeInCir(F_nodeP root, F_nodeP newNode) {
	//since it is a circular list
	//we can always put node into list as follow
	F_nodeP left = root->leftS;

	root->leftS = newNode;
	newNode->leftS = left;

	left->rightS = newNode;
	newNode->rightS = root;
}

//create default node by key and value
F_nodeP CreateNode(const lld key, const lld value) {
	F_nodeP newNode = (F_nodeP)malloc(sizeof(FNode));	//allocate new node address

	//struct part
	newNode->child = NULL;
	newNode->leftS = newNode->rightS = newNode;	//circular list
	newNode->parent = NULL;
	newNode->childCut = 0;
	newNode->treeType = 0;

	//data part
	newNode->key = key;
	newNode->value = value;

	return newNode;	//return node
}

//create default FHeap
F_heapP CreateFHeap() {
	F_heapP heap = (F_heapP)malloc(sizeof(FHeap));
	
	//init FHeap
	heap->root = NULL;
	heap->bst = CreateBST();	//init bst tree in FHeap

	return heap;
}

/*binary search tree*/

//create bst
BSTP CreateBST() {
	BSTP bst = (BSTP)malloc(sizeof(BST));
	bst->root = NULL;

	return bst;
}

//search node by key and value
TreePointer Search(BSTP bst, const lld key, const lld value) {
	TreePointer root = bst->root;
	if (root == NULL) return NULL;	//empty tree => return

	TreePointer pointer = root;	//search pointer
	while (pointer != NULL)
	{
		if (pointer->key == key && pointer->value == value) break;	//find
		else {
			//新key大於當前節點的key
			if (key > pointer->key) {
				pointer = pointer->rightChild;
			}
			else if (key < pointer->key) {
				pointer = pointer->leftChild;
			}
			else if (value > pointer->value) {
				pointer = pointer->rightChild;
			}
			else if (value < pointer->value) {
				pointer = pointer->leftChild;
			}
		}
	}

	return pointer;
}

//插入一個節點
void InsertBST(BSTP bst, TreePointer newNode) {

	//如果樹是空的 直接插入在根節點
	if (bst->root == NULL) {
		bst->root = newNode;
	}
	else {
		//get data from newnode
		lld key = newNode->key;
		lld value = newNode->value;

		TreePointer pointer = bst->root;	//新增指針指向根節點

		//向下開始塞
		while (pointer != NULL)
		{
			//新key大於當前節點的key
			if (key > pointer->key) {

				//右節點為空 將新節點加在那裡
				//非空 指針向右節點移動
				if (pointer->rightChild == NULL) {
					pointer->rightChild = newNode;
					break;
				}
				else {
					pointer = pointer->rightChild;
				}
			}
			else if (key < pointer->key) {

				//左節點為空 將新節點加在那裡
				//非空 指針向左節點移動
				if (pointer->leftChild == NULL) {
					pointer->leftChild = newNode;
					break;
				}
				else {
					pointer = pointer->leftChild;
				}
			}
			else if (value > pointer->value) {
				//右節點為空 將新節點加在那裡
				//非空 指針向右節點移動
				if (pointer->rightChild == NULL) {
					pointer->rightChild = newNode;
					break;
				}
				else {
					pointer = pointer->rightChild;
				}
			}
			else if (value < pointer->value) {

				//左節點為空 將新節點加在那裡
				//非空 指針向左節點移動
				if (pointer->leftChild == NULL) {
					pointer->leftChild = newNode;
					break;
				}
				else {
					pointer = pointer->leftChild;
				}
			}
		}
	}
}

//回傳一個新的樹節點
TreePointer NewTreePointer(const lld key, const lld value, const F_nodeP pointer) {
	TreePointer tp = (TreePointer)malloc(sizeof(node));
	tp->key = key;
	tp->value = value;
	tp->pos = pointer;

	tp->leftChild = NULL;
	tp->rightChild = NULL;

	return tp;
}

//Delete node by key from binary search tree
void DeleteBST(BSTP bst, const lld key, const lld value) {
	//this binary search tree is empty
	if (bst->root == NULL) return;

	TreePointer p = bst->root;	//create a pointer 'p' pointed to root of tree
	TreePointer parentP = NULL;	//trace parent of p

	//if p is not empty pointer
	//and the node key which pointed by 'p' doesn't equal to key
	//keeping find
	while (p != NULL && p->key != key) {
		parentP = p;	//since p must go to child, we can record p now

		//acording to key, decide p go to the left child or right 
		if (key > p->key) {
			p = p->rightChild;
		}
		else if (key < p->key) {
			p = p->leftChild;
		}
		else if (value > p->value) {
			p = p->rightChild;
		}
		else if (value < p->value) {
			p = p->leftChild;
		}
	}


	if (p == NULL) {
		//do not find node with same key
		return;
	}
	else if (p->leftChild == NULL && p->rightChild == NULL) {
		//a leaf node

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = NULL;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = NULL;
		else if (parentP == NULL) {
			bst->root = NULL;
		}
	}
	else if (p->leftChild != NULL && p->rightChild == NULL) {
		//a 1-degree node
		TreePointer childOfP = p->leftChild;	//trace child of p

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = childOfP;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = childOfP;
		else if (parentP == NULL) {
			bst->root = childOfP;
		}
	}
	else if (p->leftChild == NULL && p->rightChild != NULL) {
		//a 1-degree node
		TreePointer childOfP = p->rightChild;	//trace child of p

		//if p has parent change parent's child
		if (parentP != NULL && parentP->rightChild == p) parentP->rightChild = childOfP;
		else if (parentP != NULL && parentP->leftChild == p) parentP->leftChild = childOfP;
		else if (parentP == NULL) {
			bst->root = childOfP;
		}
	}
	else if (p->leftChild != NULL && p->rightChild != NULL) {
		//2-degree node
		//replace p node by max key in left child
		//next, delete the child(which must be 0 or 1 degree node

		TreePointer maxIn_LeftChild = p->leftChild;
		while (maxIn_LeftChild->rightChild != NULL) {
			maxIn_LeftChild = maxIn_LeftChild->rightChild;	//持續找右邊的子節點
		}

		//RecordData of the chlld
		TreePointer temp = (TreePointer)malloc(sizeof(node));
		CopyNode(temp, maxIn_LeftChild);

		DeleteBST(bst, maxIn_LeftChild->key, maxIn_LeftChild->value);	//delete child

		//set data of p as the child
		CopyNode(p, temp);

		return;
	}

	free(p);
	return;
}

//copy function of node
void CopyNode(TreePointer a, const TreePointer b) {
	a->key = b->key;
	a->pos = b->pos;
	return;
}
