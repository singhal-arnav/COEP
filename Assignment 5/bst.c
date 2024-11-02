#include <stdio.h>
#include <string.h>
#include "bst.h"
#include "stack.c"

void initBST(BST *tp) {
    *tp = NULL;
    return;
}

int monthValue(char *month) {
    if(strcmp(month, "January") == 0)
        return 1;
    if(strcmp(month, "February") == 0)
        return 2;
    if(strcmp(month, "March") == 0)
        return 3;
    if(strcmp(month, "April") == 0)
        return 4;
    if(strcmp(month, "May") == 0)
        return 5;
    if(strcmp(month, "June") == 0)
        return 6;
    if(strcmp(month, "July") == 0)
        return 7;
    if(strcmp(month, "August") == 0)
        return 8;
    if(strcmp(month, "September") == 0)
        return 9;
    if(strcmp(month, "October") == 0)
        return 10;
    if(strcmp(month, "November") == 0)
        return 11;
    if(strcmp(month, "December") == 0)
        return 12;
    return 0; //Invalid month
}

void insertNode(BST *tp, char *month) {
    node *nn = (node*)malloc(sizeof(node));
    strcpy(nn -> month, month);
    nn -> left = nn -> right = NULL;
    if(*tp == NULL){
        *tp = nn;
        return;
    }
    node *p = *tp, *q = NULL;
    while(p){
        q = p;
        if(monthValue(p -> month) > monthValue(month))
            p = p -> left;
        else if(monthValue(p -> month) < monthValue(month))
            p = p -> right;
        else{
            free(nn);
            return;
        }
    }
    if(monthValue(q -> month) > monthValue(month))
        q -> left = nn;
    else if(monthValue(q -> month) < monthValue(month))
        q -> right = nn;
    nn -> parent = q;
    
    return;
}

node* findMinNode(BST t) {
    node *p = t;
    while(p -> left)
        p = p -> left;
    
    return p;
}

void removeNode(BST *tp, char *month) {
    node *p = *tp;
    while (p != NULL && strcmp(p->month, month)) {
        if (monthValue(month) < monthValue(p->month))
            p = p->left;
        else
            p = p->right;
    }

    if (p == NULL)
        return;

    if (p->left && p->right) { //Node to be deleted has two children
        node *q = findMinNode(p->right);

        strcpy(p->month, q->month);

        if (q->parent->left == q)
            q->parent->left = q->right;
        else
            q->parent->right = q->right;

        if (q->right)
            q->right->parent = q->parent;

        free(q);
    }
    else if (p->left || p->right) { //Node to be deleted has only one child
        node *child = (p->left) ? p->left : p->right;

        if (p == *tp) {
            *tp = child;
            child->parent = NULL;
        }
        else {
            if (p->parent->left == p)
                p->parent->left = child;
            else
                p->parent->right = child;

            child->parent = p->parent;
        }

        free(p);
    }
    else { // Node to be deleted has no child (leaf node)
        if (p == *tp) {
            *tp = NULL;
        }
        else {
            if (p->parent->left == p)
                p->parent->left = NULL;
            else
                p->parent->right = NULL;
        }

        free(p);
    }
}

void traverse(BST t) { //non-recursive preorder traversal
    if (t == NULL) {
        return;
    }
    node *p = t;
    stack s;
    initStack(&s);
    while (p || !isEmpty(s)) {
    	if(p){
    		printf("%s -> ", p -> month);
    		push(&s,p);
    		p = p -> left;
    	}
    	else{
    		p = pop(&s);
    		p = p -> right;
    	}      
    }
    printf("\n");
    return;
}

void destroyTree(BST *tp) {
    if(*tp == NULL)
        return;
    destroyTree(&((*tp) -> left));
    destroyTree(&((*tp) -> right));
    free(*tp);
    return;
}