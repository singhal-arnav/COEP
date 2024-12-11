#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

void init(BST *tp) {
    *tp = NULL;
    return;
}

void insert(BST *tp, int val) {
    node *nn = (node *)malloc(sizeof(node));
    nn -> data = val;
    nn -> lchild = nn -> rchild = NULL;

    if(*tp == NULL) {
        *tp = nn;
        return;
    }

    node *p = *tp, *q;

    while(p) {
        q = p;
        if(p -> data > val)
            p = p -> lchild;
        else if(p -> data < val)
            p = p -> rchild;
        else {
            free(nn);
            return;
        }
    }

    if(q -> data > val)
        q -> lchild = nn;
    else
        q -> rchild = nn;
    
    return;
}

void remove_node(BST *b, int key) {
    if(*b == NULL)
        return;

    node *root = *b;
    if(root->data < key)
        remove_node(&(root->rchild), key);
    else if(root->data > key)
        remove_node(&(root->lchild), key);

    else if(root->data == key)
    {
        // leaf node
        if(root->lchild == NULL && root->rchild == NULL)
        {
            free(root);
            *b = NULL;
        }

        else if(root->lchild && !root->rchild)
        {
            root->data = root->lchild->data;
            free((root->lchild));
            root->lchild = NULL;
        }

        else if(root->rchild && !root->lchild)
        {
            root->data = root->rchild->data;
            free((root->rchild));
            root->rchild = NULL;
        }
        
        else
        {
            node *curr = root->rchild;

            while(curr->lchild)
                curr = curr->lchild;
            
            root->data = curr->data;
            remove_node(&(root->rchild), curr->data);
        }
    }
    return;
}

void preorder(BST t) {
    if(t == NULL)
        return;
    printf("%d ", t -> data);
    preorder(t -> lchild);
    preorder(t -> rchild);
    return;
}

void inorder(BST t) {
    if(t == NULL)
        return;
    inorder(t -> lchild);
    printf("%d ", t -> data);
    inorder(t -> rchild);
    return;
}

void postorder(BST t) {
    if(t == NULL)
        return;
    postorder(t -> lchild);
    postorder(t -> rchild);
    printf("%d ", t -> data);
    return;
}