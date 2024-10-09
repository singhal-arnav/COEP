#include <stdlib.h>
#include <string.h>
#include "stack.h"

void init(stack *sp, int size) {
    sp -> a = (char*)malloc(sizeof(char) * size);
    sp -> size = size;
    sp -> top = -1;
}

int isEmpty(stack s) {
    if(s.top == -1)
        return 1;
    return 0;
}

void push(stack *sp, char c) {
    sp -> a[++sp -> top] = c;
    return;
}

char pop(stack *sp) {
    if(isEmpty(*sp))
        return '\0';
    return sp -> a[sp -> top--];
}

char peek(stack s) {
    if(s.top == -1)
        return '\0';
    return s.a[s.top];   
}

int check_exp(char *exp) {
    stack s;
    int i, n = strlen(exp);
    char prev_ch = '\0';

    init(&s, n);

    for(i = 0; i < n; i++) {
        if((peek(s) == '[' && exp[i] == ']') || (peek(s) == '{' && exp[i] == '}') || (peek(s) == '(' && exp[i] == ')'))
            pop(&s);
        else
            push(&s, exp[i]);
    }
    
    if(isEmpty(s))
        return 1;
    return 0;
}