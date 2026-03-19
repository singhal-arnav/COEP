#include <stdlib.h>
#include "stack.h"

void init(stack *sp) {
    sp -> top = NULL;
}

void push(stack *sp, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> data = val;
    nn -> next = sp -> top;
    sp -> top = nn;
    return;
}

int is_empty(stack s) {
    if(s.top)
        return 0;
    return 1;
}

int pop(stack *sp) {
    if(!is_empty(*sp)) {
        node *p = sp -> top;
        sp -> top = sp -> top -> next;
        int val = p -> data;
        free(p);
        return val;
    }
    return INT_MIN;
}

int dec_to_bin(int num) {
    stack s;
    init(&s);

    while(num) {
        push(&s, num % 2);
        num /= 2;
    }

    int bin = 0;
    while(!is_empty(s)) {
        bin *= 10;
        bin += pop(&s);
    }

    return bin;
}