#include "DLL.h"
#include <stdio.h>
#include <stdlib.h>

void init_DLL(DLL *lp) {
    lp -> front = NULL;
    lp -> rear = NULL;
}

void insert_beg(DLL *lp, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> prev = NULL;
    nn -> next = lp -> front;

    if(!is_empty(*lp)) {
        lp -> front -> prev = nn;
        lp -> front = nn;
    }
    else {
        lp -> front = nn;
        lp -> rear = nn;
    }

    return;
}

void insert_end(DLL *lp, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> next = NULL;
    nn -> prev = lp -> rear;
    
    if(!is_empty(*lp)) {
        lp -> rear -> next = nn;
        lp -> rear = nn;
    }
    else {
        lp -> front = nn;
        lp -> rear = nn;
    }

    return;
}

void insert_pos(DLL *lp, int val) { //incomplete
    node *p = lp -> front;

    for(int i = 0; i < val; i++)
        p = p -> next;
    
    node *nn = (node*)malloc(sizeof(node));
    nn -> prev = p;
    nn -> next = p -> next;
    
    if(p -> next)
        p -> next -> prev = nn;
    p -> next = nn;

    return;
}

int is_empty(DLL l) {
    if(l.front == NULL)
        return 1;
    return 0;
}

void remove_beg(DLL *lp) {
    if(is_empty(*lp))
        return;
    
    node *p = lp -> front;

    if(lp -> front -> next == NULL) {
        lp -> front = NULL;
        lp -> rear = NULL;
    }
    else {
        lp -> front = lp -> front -> next;
        lp -> front -> prev = NULL;
    }

    free(p);
    return;
}

void remove_end(DLL *lp) {
    if(is_empty(*lp))
        return;
    
    node *p = lp -> rear;

    if(lp -> rear -> prev == NULL) {
        lp -> front = NULL;
        lp -> rear = NULL;
    }
    else {
        lp -> rear = lp -> rear -> prev;
        lp -> rear -> next = NULL;
    }

    free(p);
    return;
}

void remove_pos(DLL *lp, int pos) {

}

void sort(DLL *lp) {

}

void displayRL(DLL l) {

}

void displayLR(DLL l) {

}

int is_palindrome(DLL l) {

}

void remove_duplicates(DLL *lp) {

}