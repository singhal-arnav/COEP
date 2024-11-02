#include <stdlib.h>
#include "stack.h"

void initStack(stack *sp) {
    sp -> top = NULL;
}

void push(stack *sp, struct node *n) {
    stacknode *nn = (stacknode*)malloc(sizeof(stacknode));
    nn -> data = n;
    nn -> next = sp -> top;
    sp -> top = nn;
    return;
}

int isEmpty(stack s) {
    if(s.top)
        return 0;
    return 1;
}

struct node* pop(stack *sp) {
    if(!isEmpty(*sp)) {
        stacknode *p = sp -> top;
        sp -> top = sp -> top -> next;
        struct node *n = p -> data;
        free(p);
        return n;
    }
    return NULL;
}