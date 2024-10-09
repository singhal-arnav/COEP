#include "ascii.h"

void init_ASCII(ASCII* L) {
    L -> front = NULL;
    L -> rear = NULL;
}

int isempty(ASCII L){
    if(L.front ==NULL)
         return 1;
    return 0;
}

void insert_at_beg(ASCII* L, int num) {
    node* nn = (node*)malloc(sizeof(node));
    nn->prev = NULL;
    nn->next = L->front;
    nn->data = num;
    
    if(isempty(*L)) {
        L->front = nn;
        L->rear = nn;
    }
    L->front->prev = nn;
    L->front = nn;
    return;
}

void ASCII_of(ASCII* L, char c) {
    int num = c;
    while(num) {
        insert_at_beg(L, num % 10);
        num /= 10;
    }
    return;
}

void traverse(ASCII L) {
    if(isempty(L))
        return;

    node* p = L.front;
    printf("%d", p->data);
    while(p->next) {
        p = p->next;
        printf(" <-> %d", p->data);
    }
    printf("\n");
    return;
}

void Destroy(ASCII* L) {
    node *p = L->front, *q;
    while(p->next) {
        q = p -> next;
        free(p);
        p = q;
    }
    free(p);
    L->front = NULL;
    L->rear = NULL;
    return;
}