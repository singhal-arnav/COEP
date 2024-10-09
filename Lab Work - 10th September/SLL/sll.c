#include "SLL.h"
#include <stdio.h>
#include <stdlib.h>

void init_SLL(SLL *lp) {
    *lp = NULL;
    return;
}

void append(SLL* lp, int val) {
    node* nn = (node*) malloc(sizeof(node));
    nn -> data = val;
    nn -> next = NULL;

    if(*lp) {
        node* p = *lp;
        while(p -> next)
            p = p -> next;
        p -> next = nn;
    }
    else
        *lp = nn;
    
    return;
}

void traverse(SLL l) {
    node* p = l;
    
    if(p) {
        while(p -> next) {
            printf("%d ", p -> data);
            p = p -> next;
        }
        printf("%d\n", p -> data);
    }

    return;
}

void insert_at_beg(SLL* lp, int val) {
    node* nn = (node*) malloc(sizeof(node));
    nn -> data = val;
    nn -> next = *lp;
    *lp = nn;

    return;
}

void remove_at_pos(SLL* lp, int pos) {
    node *p = *lp, *q = NULL;
    for(int i = 0; i < pos; i++) {
        if(p == NULL)
            break;
        q = p;
        p = p -> next;
    }

    q -> next = p -> next;
    free(p);

    return;
}

int len(SLL l) {
    node* p = l;
    int i = 0;

    if(p) {
        while(p) {
            p = p -> next;
            i++;
        }
    }

    return i;
}