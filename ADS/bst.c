#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *lchild, *rchild;
} node;

typedef struct tree {
    node *root;
} tree;

typedef struct stacknode {
    struct node *data;
    struct stacknode *next;
} stacknode;

typedef struct stack {
    stacknode *top;
} stack;

void init_tree(tree *tp);
node* create_node(int val);
void insert_node(tree *tp, int val);
node* search_max(tree *tp);
void preorder(tree tp);
void inorder(tree tp);
void postorder(tree tp);
void print_tree(node *root, int space, int is_right);
void display_tree(tree tp);

void initStack(stack *sp);
void push(stack *sp, struct node *n);
int isEmpty(stack s);
struct node* pop(stack *sp);

int main() {
    tree bst;
    init_tree(&bst);
    
    printf("Inserting nodes: 50, 30, 70, 20, 40, 60, 80, 10, 25, 65\n\n");
    insert_node(&bst, 50);
    insert_node(&bst, 30);
    insert_node(&bst, 70);
    insert_node(&bst, 20);
    insert_node(&bst, 40);
    insert_node(&bst, 60);
    insert_node(&bst, 80);
    insert_node(&bst, 10);
    insert_node(&bst, 25);
    insert_node(&bst, 65);
    
    printf("Tree Structure:\n\n");
    display_tree(bst);
    printf("\n\n");
    
    node *max_node = search_max(&bst);
    if (max_node)
        printf("Maximum value in tree: %d\n\n", max_node->data);
    
    printf("Iterative Traversals:\n");
    printf("Pre-order:  ");
    preorder(bst);
    printf("\n");
    
    printf("In-order:   ");
    inorder(bst);
    printf("\n");
    
    printf("Post-order: ");
    postorder(bst);
    printf("\n");
    
    return 0;
}

void init_tree(tree *tp) {
    tp->root = NULL;
}

node* create_node(int val) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->data = val;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    return new_node;
}

void insert_node(tree *tp, int val) {
    node *new_node = create_node(val);
    
    if (tp->root == NULL) {
        tp->root = new_node;
        return;
    }
    
    node *curr = tp->root;
    node *parent = NULL;
    
    while (curr != NULL) {
        parent = curr;
        if (val < curr->data)
            curr = curr->lchild;
        else if (val > curr->data)
            curr = curr->rchild;
        else {
            free(new_node);
            return;
        }
    }
    
    if (val < parent->data)
        parent->lchild = new_node;
    else
        parent->rchild = new_node;
}

node* search_max(tree *tp) {
    if (tp->root == NULL)
        return NULL;
    
    node *curr = tp->root;
    while (curr->rchild != NULL) {
        curr = curr->rchild;
    }
    return curr;
}

void preorder(tree tp) {
    if (tp.root == NULL)
        return;
    
    stack s;
    initStack(&s);
    push(&s, tp.root);
    int first = 1;
    
    while (!isEmpty(s)) {
        node *curr = pop(&s);
        if (!first)
            printf(" -> ");
        printf("%d", curr->data);
        first = 0;
        
        if (curr->rchild)
            push(&s, curr->rchild);
        if (curr->lchild)
            push(&s, curr->lchild);
    }
}

void inorder(tree tp) {
    if (tp.root == NULL)
        return;
    
    stack s;
    initStack(&s);
    node *curr = tp.root;
    int first = 1;
    
    while (curr != NULL || !isEmpty(s)) {
        while (curr != NULL) {
            push(&s, curr);
            curr = curr->lchild;
        }
        curr = pop(&s);
        if (!first)
            printf(" -> ");
        printf("%d", curr->data);
        first = 0;
        curr = curr->rchild;
    }
}

void postorder(tree tp) {
    if (tp.root == NULL)
        return;
    
    stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    
    push(&s1, tp.root);
    
    while (!isEmpty(s1)) {
        node *curr = pop(&s1);
        push(&s2, curr);
        
        if (curr->lchild)
            push(&s1, curr->lchild);
        if (curr->rchild)
            push(&s1, curr->rchild);
    }
    
    int first = 1;
    while (!isEmpty(s2)) {
        node *curr = pop(&s2);
        if (!first)
            printf(" -> ");
        printf("%d", curr->data);
        first = 0;
    }
}

int get_height(node *root) {
    if (root == NULL)
        return 0;
    int left_h = get_height(root->lchild);
    int right_h = get_height(root->rchild);
    return (left_h > right_h ? left_h : right_h) + 1;
}

void print_tree_helper(node *root, int space, int height, char *prefix, int is_left) {
    if (root == NULL)
        return;
    
    if (root->rchild) {
        char new_prefix[100];
        sprintf(new_prefix, "%s%s", prefix, is_left ? "│   " : "    ");
        print_tree_helper(root->rchild, space, height - 1, new_prefix, 0);
    }
    
    printf("%s", prefix);
    printf("%d\n", root->data);
    
    if (root->lchild) {
        char new_prefix[100];
        sprintf(new_prefix, "%s%s", prefix, is_left ? "    " : "│   ");
        print_tree_helper(root->lchild, space, height - 1, new_prefix, 1);
    }
}

void print_tree(node *root, int space, int is_right) {
    if (root == NULL)
        return;
    
    space += 6;
    
    print_tree(root->rchild, space, 1);
    
    if (root->rchild) {
        printf("\n");
        for (int i = 6; i < space; i++)
            printf(" ");
        printf("/\n");
    }
    
    printf("\n");
    for (int i = 6; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);

    if (root->lchild) {
        printf("\n");
        for (int i = 6; i < space; i++)
            printf(" ");
        printf("\\\n");
    }

    print_tree(root->lchild, space, 0);
}

void display_tree(tree tp) {
    if (tp.root == NULL) {
        printf("Tree is empty\n");
        return;
    }
    print_tree(tp.root, 0, 0);
}

void initStack(stack *sp) {
    sp->top = NULL;
}

void push(stack *sp, struct node *n) {
    stacknode *nn = (stacknode*)malloc(sizeof(stacknode));
    nn->data = n;
    nn->next = sp->top;
    sp->top = nn;
}

int isEmpty(stack s) {
    return (s.top == NULL);
}

struct node* pop(stack *sp) {
    if (isEmpty(*sp))
        return NULL;
    
    stacknode *p = sp->top;
    sp->top = sp->top->next;
    struct node *n = p->data;
    free(p);
    return n;
}
