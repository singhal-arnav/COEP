#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1

typedef struct node {
    int data;
    time_t timestamp;
    int colour;
    struct node *parent, *left, *right;
} node;

typedef struct rbtree {
    struct node *root;
    struct node *NIL;
} rbtree;

void init(rbtree *tp);
node* create_node(rbtree *tp, int val);
void insert(rbtree *tp, int val);
void left_rotate(rbtree *tp, node *x);
void right_rotate(rbtree *tp, node *y);
void insert_fixup(rbtree *tp, node *z);
node* search(rbtree *tp, int val);
void inorder(rbtree *tp, node *np);
void inorder_by_timestamp(rbtree *tp, node *np);
void collect_nodes(node *np, node **arr, int *index, node *NIL);
int compare_timestamp(const void *a, const void *b);
void sort_by_timestamp(rbtree *tp);

int main() {
    rbtree tree;
    init(&tree);
    
    printf("Inserting values: 50, 30, 70, 20, 40, 60, 80, 10, 25, 35\n");
    insert(&tree, 50);
    insert(&tree, 30);
    insert(&tree, 70);
    insert(&tree, 20);
    insert(&tree, 40);
    insert(&tree, 60);
    insert(&tree, 80);
    insert(&tree, 10);
    insert(&tree, 25);
    insert(&tree, 35);
    
    printf("\nInorder Traversal:\n");
    inorder(&tree, tree.root);
    printf("\n\n");
    
    int search_values[] = {40, 60, 100};
    for (int i = 0; i < 3; i++) {
        node *found = search(&tree, search_values[i]);
        if (found != tree.NIL) {
            char time_str[26];
            struct tm *tm_info = localtime(&found->timestamp);
            strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
            printf("Found %d - Inserted at: %s\n", search_values[i], time_str);
        } else {
            printf("Value %d not found in tree\n", search_values[i]);
        }
    }
    
    printf("\nSorting by timestamp:\n");
    sort_by_timestamp(&tree);
    
    return 0;
}

void init(rbtree *tp) {
    tp->NIL = (node *)malloc(sizeof(node));
    tp->NIL->colour = BLACK;
    tp->NIL->left = tp->NIL->right = tp->NIL->parent = NULL;
    tp->root = tp->NIL;
}

node* create_node(rbtree *tp, int val) {
    node *nn = (node *)malloc(sizeof(node));
    nn->data = val;
    nn->timestamp = time(NULL);
    nn->colour = RED;
    nn->left = tp->NIL;
    nn->right = tp->NIL;
    nn->parent = tp->NIL;
    return nn;
}

void insert(rbtree *tp, int val) {
    node *nn = create_node(tp, val);
    
    if (tp->root == tp->NIL) {
        tp->root = nn;
        nn->parent = tp->NIL;
    } else {
        node *p = tp->root, *q = tp->NIL;
        
        while (p != tp->NIL) {
            q = p;
            
            if (val < p->data)
                p = p->left;
            else if (val > p->data)
                p = p->right;
            else {
                free(nn);
                return;
            }
        }
        
        nn->parent = q;
        if (val < q->data)
            q->left = nn;
        else
            q->right = nn;
    }
    
    insert_fixup(tp, nn);
}

void left_rotate(rbtree *tp, node *x) {
    node *y = x->right;
    x->right = y->left;
    
    if (y->left != tp->NIL)
        y->left->parent = x;
    
    y->parent = x->parent;
    
    if (x->parent == tp->NIL)
        tp->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    
    y->left = x;
    x->parent = y;
}

void right_rotate(rbtree *tp, node *y) {
    node *x = y->left;
    y->left = x->right;
    
    if (x->right != tp->NIL)
        x->right->parent = y;
    
    x->parent = y->parent;
    
    if (y->parent == tp->NIL)
        tp->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;
    
    x->right = y;
    y->parent = x;
}

void insert_fixup(rbtree *tp, node *z) {
    while (z->parent->colour == RED) {
        if (z->parent == z->parent->parent->left) {
            node *y = z->parent->parent->right;
            
            if (y->colour == RED) {
                // Case 1: Uncle is red
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    // Case 2: Uncle is black, z is right child
                    z = z->parent;
                    left_rotate(tp, z);
                }
                // Case 3: Uncle is black, z is left child
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                right_rotate(tp, z->parent->parent);
            }
        } else {
            node *y = z->parent->parent->left;
            
            if (y->colour == RED) {
                // Case 1: Uncle is red
                z->parent->colour = BLACK;
                y->colour = BLACK;
                z->parent->parent->colour = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    // Case 2: Uncle is black, z is left child
                    z = z->parent;
                    right_rotate(tp, z);
                }
                // Case 3: Uncle is black, z is right child
                z->parent->colour = BLACK;
                z->parent->parent->colour = RED;
                left_rotate(tp, z->parent->parent);
            }
        }
    }
    tp->root->colour = BLACK;
}

node* search(rbtree *tp, int val) {
    node *curr = tp->root;
    
    while (curr != tp->NIL) {
        if (val == curr->data)
            return curr;
        else if (val < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }
    
    return tp->NIL;  // Not found
}

void inorder(rbtree *tp, node *np) {
    if (np == tp->NIL)
        return;
    
    inorder(tp, np->left);
    printf("%d(%c) -> ", np->data, np->colour == RED ? 'R' : 'B');
    inorder(tp, np->right);
}

void collect_nodes(node *np, node **arr, int *index, node *NIL) {
    if (np == NIL)
        return;
    
    collect_nodes(np->left, arr, index, NIL);
    arr[(*index)++] = np;
    collect_nodes(np->right, arr, index, NIL);
}

int compare_timestamp(const void *a, const void *b) {
    node *n1 = *(node **)a;
    node *n2 = *(node **)b;
    return difftime(n1->timestamp, n2->timestamp);
}

void sort_by_timestamp(rbtree *tp) {
    if (tp->root == tp->NIL) {
        printf("Tree is empty\n");
        return;
    }
    
    node **nodes = (node **)malloc(sizeof(node *) * 100);
    int count = 0;
    collect_nodes(tp->root, nodes, &count, tp->NIL);
    
    qsort(nodes, count, sizeof(node *), compare_timestamp);
    
    printf("Nodes sorted by insertion timestamp:\n");
    for (int i = 0; i < count; i++) {
        char time_str[26];
        struct tm *tm_info = localtime(&nodes[i]->timestamp);
        strftime(time_str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
        printf("%d - Inserted at: %s\n", nodes[i]->data, time_str);
    }
    
    free(nodes);
}
