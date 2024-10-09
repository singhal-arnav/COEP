#include <stdlib.h>
#include <string.h>
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

char pop(stack *sp) {
    if(isEmpty(*sp))
        return '\0';
    return sp -> a[sp -> top--];
}

void reverse_string(char *str) {
    stack s;
    int i, n = strlen(str);
    init(&s, n);

    for(i = 0; i < n; i++)
        push(&s, str[i]);
    
    for(i = 0; i < n; i++)
        str[i] = pop(&s);
    
    return;
}