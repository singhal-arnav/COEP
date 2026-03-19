#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{
    int key;
    int degree;
    struct node *parent;
    struct node *child;
    struct node *left;
    struct node *right;
    int mark;
};

struct node* minNode = NULL;

struct node* createNode(int key);
void insertNode(int key);
void displayHeap();
void findMin();
void linkHeaps(struct node* y, struct node* x);
void extractMin();
struct node* unite(struct node* h1, struct node* h2);
void decreaseKey(struct node* x, int newKey);

int main() {
    printf("Inserting keys: 10, 20, 30, 5, 15, 25, 8, 12\n");
    insertNode(10);
    insertNode(20);
    insertNode(30);
    insertNode(5);
    insertNode(15);
    insertNode(25);
    insertNode(8);
    insertNode(12);
    displayHeap();
    printf("\n");
    
    findMin();
    printf("\n");
    
    printf("Extracting minimum from heap:\n");
    extractMin();
    displayHeap();
    findMin();
    printf("\nExtracting minimum again:\n");
    extractMin();
    displayHeap();
    findMin();
    printf("\n");
    
    printf("Creating second heap with keys: 3, 17, 24\n");
    struct node* h2 = NULL;
    h2 = createNode(3);
    
    struct node* node17 = createNode(17);
    h2->right = node17;
    node17->left = h2;
    node17->right = h2;
    h2->left = node17;
    
    struct node* node24 = createNode(24);
    node17->right = node24;
    node24->left = node17;
    node24->right = h2;
    h2->left = node24;
    
    printf("Before union:\n");
    printf("Heap 1: ");
    displayHeap();
    
    printf("Heap 2: ");
    struct node* temp = h2;
    printf("Heap elements in root list: ");
    do {
        printf("%d ", temp->key);
        temp = temp->right;
    } while (temp != h2);
    printf("\n");
    
    printf("\nUniting two heaps...\n");
    minNode = unite(minNode, h2);
    printf("After union:\n");
    displayHeap();
    findMin();
    printf("\n");
    
    printf("Current heap:\n");
    displayHeap();
    
    struct node* nodeToDecrease = minNode->right;
    int oldKey = nodeToDecrease->key;
    printf("Decreasing key from %d to 2\n", oldKey);
    decreaseKey(nodeToDecrease, 2);
    displayHeap();
    findMin();
    
    printf("\nDecreasing key of another node from %d to 1\n", minNode->right->right->key);
    decreaseKey(minNode->right->right, 1);
    displayHeap();
    findMin();
    printf("\n");
    
    return 0;
}

struct node* createNode(int key) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->left = newNode;
    newNode->right = newNode;
    newNode->mark = 0;
    return newNode;
}

void insertNode(int key) {
    struct node* newNode = createNode(key);
    if (minNode == NULL) {
        minNode = newNode;
    } 
    else {
        newNode->left = minNode;
        newNode->right = minNode->right;
        minNode->right->left = newNode;
        minNode->right = newNode;
        if(key < minNode->key)
            minNode = newNode;
    }
    printf("Inserted key %d into heap\n", key);
}

void displayHeap() {
    if (minNode == NULL) {
        printf("Empty heap\n");
        return;
    }
    printf("Heap elements in root list: ");
    struct node* temp = minNode;
    do {
        printf("%d ", temp->key);
        temp = temp->right;
    } while (temp != minNode);
    printf("\n");
}

void findMin() {
    if (minNode == NULL)
        printf("Empty heap\n");
    else
        printf("Minimum key: %d\n", minNode->key);
}

void linkHeaps(struct node* y, struct node* x){
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;

    if (x->child == NULL) {
        y->left = y;
        y->right = y;
        x->child = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    x->degree++;
    y->mark = 0;
}

void consolidate() {
    if (minNode == NULL) return;

    int D = 50;
    struct node* A[D];
    for (int i = 0; i < D; i++)
        A[i] = NULL;

    struct node* roots[100];
    int count = 0;
    struct node* w = minNode;
    do {
        roots[count++] = w;
        w = w->right;
    } while (w != minNode);

    for (int i = 0; i < count; i++) {
        struct node* x = roots[i];
        int d = x->degree;
        while (A[d] != NULL) {
            struct node* y = A[d];
            if (x->key > y->key) {
                struct node* temp = x;
                x = y;
                y = temp;
            }
            linkHeaps(y, x);
            A[d] = NULL;
            d++;
        }
        A[d] = x;
    }

    minNode = NULL;
    for (int i = 0; i < D; i++) {
        if (A[i] != NULL) {
            if (minNode == NULL) {
                A[i]->left = A[i];
                A[i]->right = A[i];
                minNode = A[i];
            } else {
                A[i]->left = minNode;
                A[i]->right = minNode->right;
                minNode->right->left = A[i];
                minNode->right = A[i];
                if (A[i]->key < minNode->key)
                    minNode = A[i];
            }
        }
    }
}

void extractMin() {
    if (minNode == NULL) {
        printf("Empty heap\n");
        return;
    }
    struct node* temp = minNode;
    struct node* child = temp->child;

    if (child != NULL) {
        struct node* c = child;
        do {
            c->parent = NULL;
            c = c->right;
        } while (c != child);

        struct node* minLeft = minNode->left;
        struct node* childLeft = child->left;

        minNode->left->right = child;
        child->left = minNode->left;
        childLeft->right = minNode;
        minNode->left = childLeft;
    }

    temp->left->right = temp->right;
    temp->right->left = temp->left;

    if (temp == temp->right) {
		minNode = NULL;
	} 
	else {
		minNode = temp->right;
		consolidate();
	}

    printf("Extracted minimum key: %d\n", temp->key);
    free(temp);
}

struct node* unite(struct node* h1, struct node* h2) {
    if (h1 == NULL) return h2;
    if (h2 == NULL) return h1;

    struct node* h1Right = h1->right;
    struct node* h2Left = h2->left;

    h1->right = h2;
    h2->left = h1;
    h1Right->left = h2Left;
    h2Left->right = h1Right;

    if (h2->key < h1->key)
        return h2;
    return h1;
}

void decreaseKey(struct node* x, int newKey) {
    if (x == NULL) {
        printf("Node is NULL\n");
        return;
    }
    if (newKey > x->key) {
        printf("New key is bigger than current key\n");
        return;
    }
    x->key = newKey;
    struct node* y = x->parent;

    if (y != NULL && x->key < y->key) {
        if (x->right == x) {
            y->child = NULL;
        } else {
            if (y->child == x) {
                y->child = x->right;
            }
            x->left->right = x->right;
            x->right->left = x->left;
        }
        y->degree--;
        
        x->parent = NULL;
        x->left = minNode;
        x->right = minNode->right;
        minNode->right->left = x;
        minNode->right = x;
        x->mark = 0;
    }

    if (x->key < minNode->key)
        minNode = x;

    printf("Decreased key to %d\n", newKey);
}
