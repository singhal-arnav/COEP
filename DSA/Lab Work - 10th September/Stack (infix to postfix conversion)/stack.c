#include <stdlib.h>
#include <limits.h>
#include "stack.h"

void init(stack *s, int len) {
    s->a = (char*)malloc(sizeof(char)*len);
    s->size = len;
    s->top = -1;
}

int isFull(stack s) {
    if(s.top == s.size - 1)
        return 1;
    else
        return 0;
}

int isEmpty(stack s) {
    if(s.top == -1)
        return 1;
    else
        return 0;
}

void push(stack *s, char d) {
    if(isFull(*s))
        return ;
    else {
        s->top++;
        s->a[s->top] = d;
        return;
    }
}

char pop(stack *s) {
    char e = '#';
    if(!isEmpty(*s)){
        e = s->a[s->top];
        s->top--;
    }
    return e;
}

char peek(stack s) {
    return s.a[s.top];
}