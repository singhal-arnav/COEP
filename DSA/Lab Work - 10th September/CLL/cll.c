#include <stdio.h>
#include <stdlib.h>
#include "cll.h"

void init_CLL(CLL *lp) {
    *lp = NULL;
    return;
}

void insert_beg(CLL *lp, int val) {
    node* nn = (node*) malloc(sizeof(node));
    nn -> data = val;
    nn -> next = *lp;
    *lp = nn;

    node *p = nn;
    while(p -> next != *lp)
        p = p -> next;
    p -> next = nn;

    return;
}

void insert_end(CLL *lp, int val) {
    node* nn = (node*) malloc(sizeof(node));
    nn -> data = val;

    if(*lp) {
        node* p = *lp;
        while(p -> next != *lp)
            p = p -> next;
        p -> next = nn;
    }
    else
        *lp = nn;
    
    nn -> next = *lp;
    
    return;
}

void insert_pos(CLL *lp, int pos, int val) { //incomplete
    node* nn = (node*) malloc(sizeof(node));
    nn -> data = val;

    if(is_empty(*lp)) {
        *lp = nn;
        nn -> next = NULL;
    }
    else {
        node *p = *lp;

        for(int i = 0; i < pos - 1; i++)
            p = p -> next;

        nn -> next = p -> next;
        
        p -> next = nn;
    }

    return;
}

int is_empty(CLL l) {
    if(l)
        return 0;
    return 1;
}

void remove_beg(CLL *lp) {
    if(is_empty(*lp))
        return;
    
    node *p, *q = *lp;

    while(p -> next != *lp)
        p = p -> next;
    p -> next = (*lp) -> next;

    *lp = (*lp) -> next;
    free(q);

    return;
}

void remove_end(CLL *lp) {
    if(is_empty(*lp))
        return;

    node *p = *lp, *q = p;

    while(p -> next != *lp) {
        q = p;
        p = p -> next;
    }
    
    q -> next = *lp;
    free(p);

    return;
}

void remove_pos(CLL *lp, int pos) {
    if(is_empty(*lp))
        return;
    
    node *p = *lp, *q = p;
    int i;
    for(i = 0; i < pos; i++) {
        q = p;
        p = p -> next;
    }

    q -> next = p -> next;
    free(p);

    return;
}

void sort(CLL *lp) {

}

void display(CLL l) {
    printf("[");
    
    node *p = l;
    
    if(!is_empty(l)) {
        while(p -> next != l) {
            printf("%d, ", p -> data);
            p = p -> next;
        }
        printf("%d", p -> data);
    }

    printf("]\n");
    return;
}