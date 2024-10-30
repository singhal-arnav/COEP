#include <stdlib.h>
#include <string.h>
#include "queue.h"

void qinit(queue *qp) {
    qp -> head = qp -> tail = NULL;
}

void enq(queue *qp, data d) {
    if(qfull(qp))
        return;
    
    node *nn = (node*)malloc(sizeof(node));
    nn -> data = d;
    if(qempty(qp)) {
        qp -> head = qp -> tail = nn;
        nn -> next = nn;
    }
    else {
        qp -> tail -> next = nn;
        nn -> next = qp -> head;
        qp -> tail = nn;
    }
    return;
}

data deq(queue *qp) {
    if(qempty(qp)) {
        data d;
        strcpy(d.name, "");
        d.age = -1;
        return d;
    }
    node *p = qp -> head, *q = NULL;
    while(p -> next != qp -> head) {
        q = p;
        p = p -> next;
    }

    qp -> tail = q;
    if(q)
        q -> next = qp -> head;
    data d = p -> data;
    free(p);
    return d;
}

int qfull(queue *qp) {
    node *p = (node*)malloc(sizeof(node));
    if(!p)
        return 1;
    free(p);
    return 0;
}

int qempty(queue *qp) {
    if(!qp -> head)
        return 1;
    return 0;
}