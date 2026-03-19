#include <stdio.h>
#include <stdlib.h>
#include "cll.h"

void init_CLL(cll *lp) {
    *lp = NULL;
    return;
}

void insert_beg(cll *lp, int val) {
    node *nn = (node *)malloc(sizeof(node));
    nn -> data = val;

    if(*lp == NULL) {
        *lp = nn;
        nn -> next = nn;
    }
    else {
        nn -> next = *lp;

        node *p = *lp;
        while(p -> next != *lp) {
            p = p -> next;
        }
        *lp = nn;
        p -> next = *lp;
    }

    return;
}

void traverse(cll l) {
    if(l) {
        node *p = l;

        printf("%d ", p -> data);
        while(p -> next != l) {
            p = p -> next;
            printf("%d ", p -> data);
        }
        pritnf("\n");
    }
    return;
}

void del_odd(cll *lp) {
    if(*lp == NULL)
        return;

    node *p = *lp;

    do {
        if(p -> data % 2) {
            
        }
    }while(p -> next != *lp);
}
