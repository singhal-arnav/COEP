#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "stack.h"

void init(stack *sp, int size) {
    sp -> a = (char*)malloc(sizeof(char) * size);
    sp -> size = size;
    sp -> top = -1;
}

int isFull(stack s) {
    if(s.top == s.size - 1)
        return 1;
    return 0;
}

int isEmpty(stack s) {
    if(s.top == -1)
        return 1;
    return 0;
}

void push(stack *sp, char c) {
    if(isFull(*sp))
        return;
    sp -> a[++sp -> top] = c;
    return;
}

int pop(stack *sp) {
    if(isEmpty(*sp))
        return INT_MIN;
    return sp -> a[sp -> top--];
}

int peek(stack s) {
    if(isEmpty(s))
        return INT_MIN;
    return s.a[s.top];
}