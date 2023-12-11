#include <stdio.h>
#include <stdlib.h>

// Node structure for Red-Black Tree
typedef struct Node* NodePointer;   //pointer of node
typedef struct Node {
    int data;
    char color;  // 'R' for red, 'B' for black
    NodePointer parent;
    NodePointer left;
    NodePointer right;
} Node;

// Red-Black Tree structure
typedef struct RedBlackTree* RBTPointer; //pointer of red black tree
typedef struct RedBlackTree{
    NodePointer root;
} RedBlackTree;

RBTPointer CreateRBTree();
NodePointer createNode(int data, char color);
void leftRotate(RBTPointer tree, NodePointer x);
void rightRotate(RBTPointer tree, NodePointer y);
void fixInsertion(RBTPointer tree, NodePointer pointer);
void insert(RBTPointer tree, int data);
void inOrderTraversal(NodePointer node);

NodePointer findMin(NodePointer node);
void transplant(RBTPointer tree, NodePointer u, NodePointer v);
void fixDeletion(RBTPointer tree, NodePointer x);
void deleteNode(RBTPointer tree, int data);

int main() {
    RBTPointer tree = CreateRBTree();

    // Insert values into the Red-Black Tree
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 15);
    insert(tree, 25);

    // Print the Red-Black Tree before deletion
    printf("In-order traversal before deletion: ");
    inOrderTraversal(tree->root);
    printf("\n");

    // Delete a node from the Red-Black Tree
    deleteNode(tree, 20);

    // Print the Red-Black Tree after deletion
    printf("In-order traversal after deletion: ");
    inOrderTraversal(tree->root);
    printf("\n");

    return 0;
}

// Function to find the minimum value node in a Red-Black Tree
NodePointer findMin(NodePointer node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to fix the Red-Black Tree properties after deletion
void fixDeletion(RBTPointer tree, NodePointer x) {
    while (x != tree->root && (x == NULL || x->color == 'B')) {
        //x at the left side of its parent
        if (x == x->parent->left) {
            NodePointer w = x->parent->right;

            //y2's case3 => change to case 1 or 2
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            if ((w->left == NULL || w->left->color == 'B') &&
                (w->right == NULL || w->right->color == 'B')) {
                //y2's case 2
                w->color = 'R';
                x = x->parent;  //check double black
            }
            else {
                //y2's case 1
                if (w->right == NULL || w->right->color == 'B') {
                    if (w->left != NULL) w->left->color = 'B';
                    w->color = 'R';
                    rightRotate(tree, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;    //keep original node's color

                //keep structure of RBTree
                x->parent->color = 'B';
                if (w->right != NULL) w->right->color = 'B';

                leftRotate(tree, x->parent);
                x = tree->root;
            }
        }
        else {
            Node* w = x->parent->left;
            if (w->color == 'R') {
                w->color = 'B';
                x->parent->color = 'R';
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }
            if ((w->right == NULL || w->right->color == 'B') &&
                (w->left == NULL || w->left->color == 'B')) {
                w->color = 'R';
                x = x->parent;
            }
            else {
                if (w->left == NULL || w->left->color == 'B') {
                    if (w->right != NULL) w->right->color = 'B';
                    w->color = 'R';
                    leftRotate(tree, w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 'B';
                if (w->left != NULL) w->left->color = 'B';
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }

    if (x != NULL) x->color = 'B';
}

// Function to delete a node from the Red-Black Tree
void deleteNode(RBTPointer tree, int data) {
    NodePointer pointer = tree->root;

    //find the data which wants to delete
    while (pointer != NULL) {
        if (data < pointer->data) {
            pointer = pointer->left;
        }
        else if (data > pointer->data) {
            pointer = pointer->right;
        }
        else {
            //find the data
            break;
        }
    }

    if (pointer == NULL) {
        printf("Node with data %d not found.\n", data);
        return;
    }

    NodePointer y = pointer;
    char y_original_color = y->color;
    NodePointer x;

    if (pointer->left == NULL) {
        //replacing pointer with right branch 
        x = pointer->right;
        transplant(tree, pointer, pointer->right);
    }
    else if (pointer->right == NULL) {
        //replacing pointer with left branch 
        x = pointer->left;
        transplant(tree, pointer, pointer->left);
    }
    else {
        //let min child to set pointer's seat
        y = findMin(pointer->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == pointer) {
            if (x != NULL) x->parent = y;
        }
        else {
            transplant(tree, y, y->right);
            y->right = pointer->right;
            if (y->right != NULL) y->right->parent = y;
        }

        transplant(tree, pointer, y);
        y->left = pointer->left;
        y->left->parent = y;
        y->color = pointer->color;
    }

    free(pointer);

    if (y_original_color == 'B') {
        fixDeletion(tree, x);
    }
}

// Helper function to replace one subtree with another
void transplant(RBTPointer tree, NodePointer u, NodePointer v) {
    
    NodePointer uParent = u->parent;    //u's parents

    if (uParent == NULL) {
        //u is null => this is a empty tree => tree set as v
        tree->root = v;
    }
    else if (u == uParent->left) {
        //put v as left child of uParent
        u->parent->left = v;
    }
    else {
        //put v as rigt child of uParent
        u->parent->right = v;
    }

    //if v is exist => v's parent set as u's parent
    if (v != NULL) {
        v->parent = uParent;
    }
}

//Create a RBTree
RBTPointer CreateRBTree() {
    RBTPointer tree = (RBTPointer)malloc(sizeof(RedBlackTree)); //allocate space for tree

    tree->root = NULL;
    return tree;
}

// Function to create a new node with the given data and color
NodePointer createNode(int data, char color) {
    NodePointer newNode = (NodePointer)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = color;

    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Function to perform left rotation
//For two node x & y
//divide data to 3 branch
void leftRotate(RBTPointer tree, NodePointer x) {
    NodePointer y = x->right;   //get pointer of y, which located at x's right
    NodePointer yLeft = y->left;   //get data branch y-L 
    NodePointer xParent = x->parent; //get parent of x

    x->right = yLeft; //set data branch yL to be x's right child

    //if data yL is not empty => set its parent to x
    if (yLeft != NULL) {
        yLeft->parent = x;
    }

    //manage relation of y and x's parent
    y->parent = xParent;
    if (xParent == NULL) {
        //x is root originally
        tree->root = y;
    }
    else if (x == xParent->left) {
        xParent->left = y;
    }
    else {
        xParent->right = y;
    }

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
//For two node x & y
//divide data to 3 branch
void rightRotate(RBTPointer tree, NodePointer y) {
    NodePointer x = y->left;
    NodePointer xRight = x->right; //right child of x
    NodePointer yParent = y->parent;    //parent of y

    //moving x right data to y's left
    y->left = xRight;
    if (xRight != NULL) {
        xRight->parent = y;
    }

    //deal with relation of x's parent and y
    x->parent = yParent;
    if (yParent == NULL) {
        tree->root = x;
    }
    else if (y == yParent->left) {
        yParent->left = x;
    }
    else {
        yParent->right = x;
    }

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree properties after insertion
void fixInsertion(RBTPointer tree, NodePointer pointer) {
    NodePointer pParent = pointer->parent;

    while (pointer != NULL && pParent != NULL && pParent->color == 'R') {
        //this pointer's parent is in a 2 or 3 node

        pParent = pointer->parent;  //update pointer's parent
        NodePointer pPParent = pParent->parent; //get grandParent of pointer

        if (pParent == pPParent->left) {
            //parent is in left side of ancester

            NodePointer nPPRight = pPParent->right;
            if (nPPRight != NULL && nPPRight->color == 'R') {
                //3 node
                //extract

                pointer->parent->color = 'B';
                nPPRight->color = 'B';
                pointer->parent->parent->color = 'R';
                pointer = pointer->parent->parent;
            }
            else {
                //2 node => LR rotate

                if (pointer == pointer->parent->right) {
                    pointer = pointer->parent;
                    leftRotate(tree, pointer);
                }
                pointer->parent->color = 'B';
                pointer->parent->parent->color = 'R';
                rightRotate(tree, pointer->parent->parent);
            }
        }
        else {
            //parent is in the right side of ancester

            NodePointer pPPLeft = pPParent->left;
            if (pPPLeft != NULL && pPPLeft->color == 'R') {
                //3 node
                //extract

                pointer->parent->color = 'B';
                pPPLeft->color = 'B';
                pointer->parent->parent->color = 'R';
                pointer = pointer->parent->parent;
            }
            else {
                //2 node
                //RL rotate

                if (pointer == pointer->parent->left) {
                    pointer = pointer->parent;
                    rightRotate(tree, pointer);
                }
                pointer->parent->color = 'B';
                pointer->parent->parent->color = 'R';
                leftRotate(tree, pointer->parent->parent);
            }
        }
    }

    //confirm tree's root is black
    tree->root->color = 'B';
}

// Function to insert a value into the Red-Black Tree
void insert(RBTPointer tree, int data) {
    NodePointer newNode = createNode(data, 'R');
    NodePointer pointer = NULL;
    NodePointer tracing = tree->root;

    while (tracing != NULL) {
        pointer = tracing;   //set pointer to point root

        //find right pos to put data
        if (newNode->data < tracing->data) {
            tracing = tracing->left;
        }
        else if(newNode->data > tracing->data) {
            tracing = tracing->right;
        }
        else {
            //there is already exist same data
            return;
        }
    }

    //pointer is the node which we find above
    newNode->parent = pointer;

    //put node into the tree
    if (pointer == NULL) {
        //there is no node in this RBT
        tree->root = newNode;
    }
    else if (newNode->data < pointer->data) {
        pointer->left = newNode;
    }
    else {
        pointer->right = newNode;
    }

    fixInsertion(tree, newNode);
}

// Function to print the Red-Black Tree in-order
void inOrderTraversal(NodePointer node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d%c ", node->data, node->color);
        inOrderTraversal(node->right);
    }
}