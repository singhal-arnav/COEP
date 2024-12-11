typedef struct node {
    int data;
    struct node *lchild, *rchild;
} node;

typedef node *BST;

void init(BST *tp);
void insert(BST *tp, int val);
void remove_node(BST *tp, int val);
void preorder(BST t);
void inorder(BST t);
void postorder(BST t);