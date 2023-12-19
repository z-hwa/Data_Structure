#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lld;

// Node structure for Red-Black Tree
typedef struct Node* NodePointer;   //pointer of node
typedef struct Node {
    lld data;
    char color;  // 'R' for red, 'B' for black
    NodePointer parent;
    NodePointer left;
    NodePointer right;
} Node;

// Red-Black Tree structure
typedef struct RedBlackTree* RBTPointer; //pointer of red black tree
typedef struct RedBlackTree {
    NodePointer root;
} RedBlackTree;

void LL(RBTPointer tree, NodePointer mid);
void RR(RBTPointer tree, NodePointer mid);
void FixInsertion(RBTPointer tree, NodePointer newNode);
void Insert(RBTPointer tree, lld data);
NodePointer CreateNode(lld data);
RBTPointer CreateTree();

void Search(RBTPointer tree, int data);
void DebugLog(char* message);

void InputWithWord();
void InputWithDigit();

void Delete(RBTPointer tree, int data);
void FixDeletion(RBTPointer tree, NodePointer p);
NodePointer FindChange(RBTPointer tree, NodePointer node);
void ChangeNodeData(RBTPointer tree, NodePointer oriData, NodePointer changeData);
void Y2Case2(RBTPointer tree, NodePointer p, int times);

void Traversal(RBTPointer tree, NodePointer p, int level);

RBTPointer tree;

int main() {

    tree = CreateTree();

    InputWithDigit();

    return 0;
}

void Traversal(RBTPointer tree, NodePointer p, int level) {
    if (p == NULL) return;

    printf("%lld, %c, %d\n", p->data, p->color, level);
    Traversal(tree, p->left, level + 1);
    Traversal(tree, p->right, level + 1);
}

void Delete(RBTPointer tree, int data) {
    NodePointer p = tree->root;

    //find the data which we want to delete
    while (p != NULL) {
        if (p->data > data) p = p->left;
        else if (p->data < data) p = p->right;
        else break;
    }

    //do not find data which we want to delet
    if (p == NULL) {
        return;
    }

    NodePointer changeData = FindChange(tree, p->right);   /* find change data under p
                                                       if don't need change => this data is already in the leaf
                                                       then changeData will be NULL
                                                       */

                                                       //if change data exist => go change
    if (changeData != NULL) {
        ChangeNodeData(tree, p, changeData);
        p = changeData; //since we change => p must reset
    }

    FixDeletion(tree, p);
}

//to keep property of red black tree
void FixDeletion(RBTPointer tree, NodePointer p) {

    if (p == tree->root) {
        //only root in this tree
        tree->root = NULL;
        free(p);
        return;
    }
    else if (p->color == 'R') {
        //method like delete y
        NodePointer parent = p->parent;

        if (parent->left == p) parent->left = NULL;
        else parent->right = NULL;

        free(p);
        return;
    }
    else if (p->color == 'B' && p->left != NULL) {
        //method like delete y1 with child at left
        NodePointer left = p->left;

        ChangeNodeData(tree, p, left);
        p->left = NULL;

        free(left);
        return;
    }
    else if (p->color == 'B' && p->right != NULL) {
        //method like delete y1 with child at right
        NodePointer right = p->right;

        ChangeNodeData(tree, p, right);
        p->right = NULL;

        free(right);
        return;
    }
    else {
        Y2Case2(tree, p, 0);
    }
}

void Y2Case2(RBTPointer tree, NodePointer p, int times) {
    //method like y2
    NodePointer parent = p->parent;
    NodePointer sibling;
    char ori_color = 'R';

    //setting value of sibling
    if (p == parent->left) sibling = parent->right;
    else sibling = parent->left;

    //child of sibling
    NodePointer left, right;
    left = sibling->left;
    right = sibling->right;

    //first into y2's case2, delete p
    if (times == 0) {
        //delete p
        if (parent->left == p) parent->left = NULL;
        else parent->right = NULL;
        free(p);
    }

    if (left != NULL && left->color == 'R') {
        //y2 case 1
        ori_color = parent->color;

        if (sibling == parent->left) {
            LL(tree, sibling);

            //color part
            left->color = 'B';
            sibling->color = ori_color;
            parent->color = 'B';
        }
        else {
            LL(tree, left);
            RR(tree, left);

            //color part
            left->color = ori_color;
            sibling->color = 'B';
            parent->color = 'B';
        }

        //update parent
        parent = p->parent;
        if (parent->left == p) parent->left = NULL;
        else parent->right = NULL;

        free(p);
        return;
    }
    else if (right != NULL && right->color == 'R') {
        //y2 case 1
        ori_color = parent->color;

        if (sibling == parent->right) {
            RR(tree, sibling);

            //color part
            sibling->left->color = 'B';
            sibling->color = ori_color;
            parent->color = 'B';
        }
        else {
            RR(tree, left);
            LL(tree, left);

            //color part
            left->color = ori_color;
            sibling->color = 'B';
            parent->color = 'B';
        }

        //update parent
        parent = p->parent;
        if (parent->left == p) parent->left = NULL;
        else parent->right = NULL;

        free(p);
        return;
    }
    else if ((left != NULL && left->color == 'B') || (right != NULL && right->color == 'B')) {
        //y2's case 2
        sibling->color = 'R';
        if (p != NULL) p->color = 'B';

        if (parent->color == 'R') parent->color = 'B';
        else if (parent != tree->root) {
            parent->color = 'B';

            //double black => change people do
            p = p->parent;
            Y2Case2(tree, p, 1);
        }
    }
    else if (sibling->color == 'R') {
        //y2's case 3
        LL(tree, sibling);  //moving sibling as parent of it's parent

        sibling->color = 'B';
        parent->color = 'R';
        Y2Case2(tree, p, 1);
    }
}

//just exchange data in each node
void ChangeNodeData(RBTPointer tree, NodePointer oriData, NodePointer changeData) {
    lld temp = oriData->data;
    oriData->data = changeData->data;
    changeData->data = temp;
}

//find data which should be change under delete method
NodePointer FindChange(RBTPointer tree, NodePointer node) {
    NodePointer p = node;
    NodePointer rec = p;

    while (p != NULL)
    {
        rec = p;
        p = p->left;   //find data under p's parent which is most smaller
    }

    if (rec == node) {
        if (rec->color == 'R') return NULL; //node's paremt and node is in the same node in 2-3-4 tree which is leaf
        else return rec;    //node is child of its parent in 2-3-4 tree
    }
    else {
        //find the change data
        return rec;
    }
}

//input mode with input digit
void InputWithDigit() {
    char order[10] = {};
    lld data;

    while (1) {
        scanf("%s", order);

        if (strcmp(order, "insert") == 0) {
            scanf("%lld", &data);
            Insert(tree, data);
        }
        else if (strcmp(order, "search") == 0) {
            scanf("%lld", &data);
            Search(tree, data);
        }
        else if (strcmp(order, "quit") == 0) {
            break;
        }
    }
}

//input mode with input word
void InputWithWord() {
    char order[10] = {};
    lld data;

    while (1) {
        scanf("%s", order);

        char word;
        if (strcmp(order, "insert") == 0) {
            getchar();
            word = getchar();
            data = word - 'A';

            Insert(tree, data);
        }
        else if (strcmp(order, "search") == 0) {
            getchar();
            word = getchar();
            data = word - 'A';
            Search(tree, data);
        }
        else if (strcmp(order, "quit") == 0) {
            break;
        }
    }
}

//find data in the tree
void Search(RBTPointer tree, int data) {
    NodePointer p = tree->root;

    while (p != NULL) {
        if (p->data > data) p = p->left;
        else if (p->data < data) p = p->right;
        else break;
    }

    if (p != NULL) {
        if (p->color == 'R') printf("red\r\n");
        else if (p->color == 'B') printf("black\r\n");
    }
    else {
        printf("Not found\r\n");
    }

    fflush(stdout);
}

//create a red black tree
RBTPointer CreateTree() {
    RBTPointer tree = (RBTPointer)malloc(sizeof(RedBlackTree));
    tree->root = NULL;

    return tree;
}

//if there are 2 red side happens => do this
//mid is the node which should sat in the middle after rotation
void LL(RBTPointer tree, NodePointer mid) {
    NodePointer d = mid->right;
    NodePointer up = mid->parent;
    NodePointer ancester = mid->parent->parent;

    //move mid to the middle seat of up, down and mid
    if (ancester != NULL) {
        if (ancester->right == up) ancester->right = mid;
        else if (ancester->left == up) ancester->left = mid;
    }
    else {
        tree->root = mid;   //this is a root node
    }
    mid->parent = ancester;

    //move up to the right side of mid
    mid->right = up;
    up->parent = mid;

    //move d to the left child of up
    up->left = d;
    if (d != NULL) d->parent = up;
}

void RR(RBTPointer tree, NodePointer mid) {
    NodePointer d = mid->left;
    NodePointer up = mid->parent;
    NodePointer ancester = mid->parent->parent;

    //move mid to the middle seat of up, down and mid
    if (ancester != NULL) {
        if (ancester->right == up) ancester->right = mid;
        else if (ancester->left == up) ancester->left = mid;
    }
    else {
        tree->root = mid;
    }
    mid->parent = ancester;

    //move up to the right side of mid
    mid->left = up;
    up->parent = mid;

    //mode d to the left child of up
    up->right = d;
    if (d != NULL) d->parent = up;
}

//keep property of Red Black Tree
//assume new node is not root node
void FixInsertion(RBTPointer tree, NodePointer newNode) {
    NodePointer parent = newNode->parent;

    if (parent == NULL) return;

    NodePointer ancester = newNode->parent->parent;
    NodePointer sibling;

    if (ancester == NULL) return;   //this tree are still under level 1 => double red point will not happen

    //case 1
    if (parent->color == 'B') return;   //don't violate rule of RBTree

    //setting sibling
    if (parent == ancester->left) sibling = ancester->right;
    else sibling = ancester->left;

    //case 2
    if (newNode == parent->left && (sibling == NULL || sibling->color == 'B')) {
        if (parent == ancester->left) {
            //case 2 => do LL
            LL(tree, parent);
            parent->color = 'B';
            ancester->color = 'R';
            newNode->color = 'R';
        }
        else if (parent == ancester->right) {
            //case 2 => do LR
            LL(tree, newNode);
            RR(tree, newNode);
            parent->color = 'R';
            ancester->color = 'R';
            newNode->color = 'B';
        }
        return;
    }
    else if (newNode == parent->right && (sibling == NULL || sibling->color == 'B')) {
        if (parent == ancester->right) {
            //case 2 => do RR
            RR(tree, parent);
            parent->color = 'B';
            ancester->color = 'R';
            newNode->color = 'R';
        }
        else if (parent == ancester->left) {
            //case 2 => do RL
            RR(tree, newNode);
            LL(tree, newNode);
            parent->color = 'R';
            ancester->color = 'R';
            newNode->color = 'B';
        }
        return;
    }

    //case 3
    if (sibling != NULL && sibling->color == 'R' && parent->color == 'R') {
        sibling->color = 'B';
        parent->color = 'B';

        if (ancester != tree->root) ancester->color = 'R';

        //promotion
        newNode = ancester;
        if (newNode != tree->root) FixInsertion(tree, newNode);
    }
}

//insert node into tree
//if this node is not root => do FixInsertion
void Insert(RBTPointer tree, lld data) {

    NodePointer newNode = CreateNode(data);
    NodePointer target = NULL;
    NodePointer pointer = tree->root;

    while (pointer != NULL) {
        target = pointer;

        if (pointer->data > data) {
            pointer = pointer->left;
        }
        else if (pointer->data < data) {
            pointer = pointer->right;
        }
        else {
            //same data exist
            return;
        }
    }

    if (target == NULL) {
        //no element in tree
        //this data is new root
        newNode->color = 'B';
        tree->root = newNode;
    }
    else {
        newNode->parent = target;

        //put node under target's child
        if (target->data > data) {
            target->left = newNode;
        }
        else {
            target->right = newNode;
        }

        FixInsertion(tree, newNode);
    }
}

//print out debug message
void DebugLog(char* message) {
    printf("%s\n", message);
    fflush(stdout);
    return;
}

//create default node with color red
NodePointer CreateNode(lld data) {
    NodePointer newNode = (NodePointer)malloc(sizeof(Node));

    newNode->color = 'R';
    newNode->data = data;

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}