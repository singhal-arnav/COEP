#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

void init(list *lp) {
    lp -> front = NULL;
    lp -> rear = NULL;
    return;
}

int is_empty(list l) {
    if(l.front == NULL)
        return 1;
    return 0;
}

void append(list *lp, int val) {
    node *nn = (node *)malloc(sizeof(node));
    if(nn) {
        nn -> data = val;
        nn -> next = NULL;
        nn -> prev = NULL;
    }
    else
        return;

    if(is_empty(*lp)) {
        lp -> front = nn;
        lp -> rear = nn;
    }
    else {
        lp -> rear -> next = nn;
        nn -> prev = lp -> rear;
        lp -> rear = nn;
    }
    return;
}

void display(list l) {
    if(is_empty(l))
        return;
    
    node *p = l.front;
    while(p) {
        printf("%d\t", p -> data);
        p = p -> next;
    }
    printf("\n");

    return;
}

void insert_at_pos(list *lp, int ind, int val) {
    node *p = lp -> front;

    int i = 0;
    while(i < ind)
        p = p -> next;
    
    node *nn = (node*)malloc(sizeof(node));
    
    
}