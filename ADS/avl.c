#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVL_node {
    char *key;
    int month_num;
    struct AVL_node* left;
    struct AVL_node* right;
    int height;
} AVL_node;

typedef struct AVL_tree {
    AVL_node* root;
} AVL_tree;

AVL_tree* create_avl_tree();
int get_month_number(char* month);
AVL_node* create_node(char* key);
int max(int a, int b);
int height(AVL_node* node);
int get_balance(AVL_node* node);
AVL_node* rotate_right(AVL_node* y);
AVL_node* rotate_left(AVL_node* x);
AVL_node* insert_node(AVL_node* node, char* key);
void insert(AVL_tree* tree, char* key);
void preorder(AVL_node* root);
void inorder(AVL_node* root);
void postorder(AVL_node* root);

int main() {
    AVL_tree* tree = create_avl_tree();
    
    char* months[] = {"December", "January", "April", "March", "July", 
                      "August", "October", "February", "November", "May", "June"};
    int n = sizeof(months) / sizeof(months[0]);
    
    printf("Inserting months into AVL tree (based on chronological order):\n");
    for (int i = 0; i < n; i++) {
        printf("Inserting: %s\n", months[i]);
        insert(tree, months[i]);
    }
    
    printf("\nTree Traversals:\n");
    
    printf("Preorder:  ");
    preorder(tree->root);
    printf("\n");
    
    printf("Inorder:   ");
    inorder(tree->root);
    printf("\n");
    
    printf("Postorder: ");
    postorder(tree->root);
    printf("\n");
    
    return 0;
}

AVL_tree* create_avl_tree() {
    AVL_tree* tree = (AVL_tree*)malloc(sizeof(AVL_tree));
    tree->root = NULL;
    return tree;
}

int get_month_number(char* month) {
    if (strcmp(month, "January") == 0) return 1;
    if (strcmp(month, "February") == 0) return 2;
    if (strcmp(month, "March") == 0) return 3;
    if (strcmp(month, "April") == 0) return 4;
    if (strcmp(month, "May") == 0) return 5;
    if (strcmp(month, "June") == 0) return 6;
    if (strcmp(month, "July") == 0) return 7;
    if (strcmp(month, "August") == 0) return 8;
    if (strcmp(month, "September") == 0) return 9;
    if (strcmp(month, "October") == 0) return 10;
    if (strcmp(month, "November") == 0) return 11;
    if (strcmp(month, "December") == 0) return 12;
    return 0;
}

AVL_node* create_node(char* key) {
    AVL_node* node = (AVL_node*)malloc(sizeof(AVL_node));
    node->key = strdup(key);
    node->month_num = get_month_number(key);
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(AVL_node* node) {
    if (!node) return 0;
    return node->height;
}

int get_balance(AVL_node* node) {
    if (!node) return 0;
    return height(node->left) - height(node->right);
}

AVL_node* rotate_right(AVL_node* y) {
    AVL_node* x = y->left;
    AVL_node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    return x;
}

AVL_node* rotate_left(AVL_node* x) {
    AVL_node* y = x->right;
    AVL_node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    return y;
}

AVL_node* insert_node(AVL_node* node, char* key) {
    int key_num = get_month_number(key);
    
    if (!node) 
        return create_node(key);
    
    if (key_num < node->month_num)
        node->left = insert_node(node->left, key);
    else if (key_num > node->month_num)
        node->right = insert_node(node->right, key);
    else
        return node;
    
    node->height = 1 + max(height(node->left), height(node->right));
    
    int balance = get_balance(node);
    
    // Left Left Case
    if (balance > 1 && key_num < node->left->month_num)
        return rotate_right(node);
    
    // Right Right Case
    if (balance < -1 && key_num > node->right->month_num)
        return rotate_left(node);
    
    // Left Right Case
    if (balance > 1 && key_num > node->left->month_num) {
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    
    // Right Left Case
    if (balance < -1 && key_num < node->right->month_num) {
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    
    return node;
}

void insert(AVL_tree* tree, char* key) {
    tree->root = insert_node(tree->root, key);
}

void preorder(AVL_node* root) {
    static int first = 1;
    if (root == NULL)
        return;
    
    if (!first)
        printf(" -> ");
    printf("%s", root->key);
    first = 0;
    
    preorder(root->left);
    preorder(root->right);
}

void inorder(AVL_node* root) {
    static int first = 1;
    if (root == NULL)
        return;
    
    inorder(root->left);
    
    if (!first)
        printf(" -> ");
    printf("%s", root->key);
    first = 0;
    
    inorder(root->right);
}

void postorder(AVL_node* root) {
    static int first = 1;
    if (root == NULL)
        return;
    
    postorder(root->left);
    postorder(root->right);
    
    if (!first)
        printf(" -> ");
    printf("%s", root->key);
    first = 0;
}
