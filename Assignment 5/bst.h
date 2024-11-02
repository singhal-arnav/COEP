typedef struct node {
    char month[10];
    struct node *left, *right, *parent;
}node;

typedef node* BST;

void initBST(BST *tp);
int monthValue(char *month);
void insertNode(BST *tp, char *month);
void removeNode(BST *tp, char *month);
void traverse(BST t);
void destroyTree(BST *tp);
