#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Node {
    int key; 
    int degree; 
    struct Node *parent;  
    struct Node *child;  
    struct Node *sibling; 
} Node;

Node* createNode(int key);
Node* createBinomialHeap();
void link(Node* y, Node* z);
Node* merge(Node* H1, Node* H2);
Node* unionHeaps(Node* H1, Node* H2);
Node* insert(Node* H, int key);
int findMin(Node* H);
Node* extractMin(Node* H);
Node* decreaseKey(Node* H, Node* x, int newKey);
void printHeap(Node* H);
void printTree(Node* node, int level);
Node* findNode(Node* H, int key);

int main() {
    Node* heap1 = createBinomialHeap();
    printf("Creating Heap 1 and inserting: 10, 20, 30, 5, 40\n");
    heap1 = insert(heap1, 10);
    heap1 = insert(heap1, 20);
    heap1 = insert(heap1, 30);
    heap1 = insert(heap1, 5);
    heap1 = insert(heap1, 40);
    printf("\nHeap 1 structure:\n");
    printHeap(heap1);
	
    printf("\nCreating Heap 2 and inserting: 15, 25, 8, 35\n");
    Node* heap2 = createBinomialHeap();
    heap2 = insert(heap2, 15);
    heap2 = insert(heap2, 25);
    heap2 = insert(heap2, 8);
    heap2 = insert(heap2, 35);
    printf("\nHeap 2 structure:\n");
    printHeap(heap2);
	
    printf("\nMinimum in Heap 1: %d\n", findMin(heap1));
    printf("Minimum in Heap 2: %d\n", findMin(heap2));
	
    printf("\nUniting Heap 1 and Heap 2...\n");
    Node* unionHeap = unionHeaps(heap1, heap2);
    printf("\nUnited Heap structure:\n");
    printHeap(unionHeap);
    printf("\nMinimum in United Heap: %d\n\n", findMin(unionHeap));
	
    Node* nodeToDecrease = findNode(unionHeap, 30);
    if (nodeToDecrease) {
        printf("Decreasing key 30 to 3...\n");
        unionHeap = decreaseKey(unionHeap, nodeToDecrease, 3);
        printf("\nHeap after decrease key:\n");
        printHeap(unionHeap);
        printf("\nMinimum after decrease key: %d\n\n", findMin(unionHeap));
    }

    printf("Extracting minimum (key = %d)...\n", findMin(unionHeap));
    unionHeap = extractMin(unionHeap);
    printf("\nHeap after extracting minimum:\n");
    printHeap(unionHeap);
    printf("\nNew minimum: %d\n", findMin(unionHeap));

    printf("\nExtracting minimum again (key = %d)...\n", findMin(unionHeap));
    unionHeap = extractMin(unionHeap);
    printf("\nHeap after second extraction:\n");
    printHeap(unionHeap);
    printf("\nNew minimum: %d\n", findMin(unionHeap));

    return 0;
}

Node* createNode(int key){
    Node* newNode= (Node*)malloc(sizeof(Node));
    newNode->key= key;
    newNode->degree= 0;
    newNode->parent= NULL;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

Node* createBinomialHeap(){
    return NULL;
}

void link(Node* y, Node* z){
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}

Node* merge(Node* H1, Node* H2){
    if(!H1){
    	return H2;
    }
    if(!H2){
    	return H1;
    }

    Node* result= NULL;
    Node *prev= NULL, *curr = NULL;
    
    while(H1 && H2){
        if(H1->degree <= H2->degree){
            curr = H1;
            H1 = H1->sibling;
        } 
        else{
            curr = H2;
            H2 = H2->sibling;
        }

        if(!result){
        	result = curr;
        }
        else{
        	prev->sibling = curr;
        }
        prev = curr;
    }

    if(H1){
    	prev->sibling = H1;
    }
    if(H2){
    	prev->sibling = H2;
    }
    return result;
}

Node* unionHeaps(Node* H1, Node* H2){
    Node* mergedHeap= merge(H1, H2);

    if(!mergedHeap){
    	return NULL;
    }

    Node* prev= NULL;
    Node* curr= mergedHeap;
    Node* next= mergedHeap->sibling;

    while(next){
        if(curr->degree != next->degree || (next->sibling && next->sibling->degree == curr->degree)){
            prev= curr;
            curr= next;
        } 
        else if(curr->key <= next->key){
            curr->sibling = next->sibling;
            link(next, curr);
        } 
        else{
            if(!prev){
            	mergedHeap = next;
            }
            else{
            prev->sibling = next;
            }
            link(curr, next);
            curr = next;
        }
        next = curr->sibling;
    }
    return mergedHeap;
}

Node* insert(Node* H, int key) {
    Node* newNode= createNode(key);
    return unionHeaps(H, newNode);
}

int findMin(Node* H){
    if(!H){
        printf("Heap is empty\n");
        return INT_MAX;
    }

    int min = INT_MAX;
    Node* curr = H;

    while(curr){
        if(curr->key < min){
        	min = curr->key;
        }
        curr = curr->sibling;
    }
    return min;
}

Node* extractMin(Node* H){
    if(!H){
        printf("Heap is empty\n");
        return NULL;
    }

    Node* prevMin = NULL;
    Node* min = H;
    Node* prev = NULL;
    Node* curr = H;
    
    while(curr->sibling){
        if(curr->sibling->key < min->key){
            min = curr->sibling;
            prevMin = curr;
        }
        curr = curr->sibling;
    }

    if(prevMin){
    	prevMin->sibling = min->sibling;
    }
    else{
    	H = min->sibling;
    }

    Node* childList= min->child;
    Node* reversed= NULL;
    
    while(childList){
        Node* next= childList->sibling;
        childList->sibling= reversed;
        reversed= childList;
        childList= next;
    }

    free(min);
    return unionHeaps(H, reversed);
}

Node* decreaseKey(Node* H, Node* x, int newKey){
    if(newKey > x->key){
        printf("New key is greater than current key\n");
        return H;
    }
    x->key = newKey;
    Node* curr = x;
    Node* parent = x->parent;

    while (parent && curr->key < parent->key){
        int temp = curr->key;
        curr->key = parent->key;
        parent->key = temp;
        curr = parent;
        parent = parent->parent;
    }

    return H;
}

Node* findNode(Node* H, int key) {
    if (!H) return NULL;
    
    Node* curr = H;
    while (curr) {
        if (curr->key == key) return curr;
        
        Node* found = findNode(curr->child, key);
        if (found) return found;
        
        curr = curr->sibling;
    }
    return NULL;
}

void printTree(Node* node, int level) {
    if (!node) return;
    
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("└─ %d\n", node->key);
    
    printTree(node->child, level + 1);
    
    if (level == 0) {
        printTree(node->sibling, level);
    }
}

void printHeap(Node* H) {
    if (!H) {
        printf("Heap is empty\n");
        return;
    }
    
    Node* curr = H;
    int treeNum = 1;
    
    while (curr) {
        printf("\nBinomial Tree B%d (degree %d, root = %d):\n", 
               curr->degree, curr->degree, curr->key);
        printf("└─ %d\n", curr->key);
        
        Node* child = curr->child;
        int childLevel = 1;
        while (child) {
            for (int i = 0; i < childLevel; i++) {
                printf("  ");
            }
            printf("└─ %d\n", child->key);
            
            Node* grandchild = child->child;
            int gcLevel = childLevel + 1;
            while (grandchild) {
                printTree(grandchild, gcLevel);
                grandchild = grandchild->sibling;
            }
            
            child = child->sibling;
        }
        
        curr = curr->sibling;
        treeNum++;
    }
    printf("\n");
}
