#include <stdlib.h>
#include "dll.h"

void init(dll *lp) {
    *lp = NULL;
    return;
}

void append(dll *lp, int val) {
    node *nn = (node *)malloc(sizeof(node));
    nn -> data = val;
    nn -> next = NULL;

    if(*lp == NULL) {
        *lp = nn;
        nn -> prev = NULL;
    }
    else {
        node *p = *lp;
        while(p -> next)
            p = p -> next;
        p -> next = nn;
        nn -> prev = p;
    }
    
    return;
}

int count(dll l) {
    node *p = l;
    int len = 0;

    while(p) {
        p = p -> next;
        len++;
    }

    return len;
}