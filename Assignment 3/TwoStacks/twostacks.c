#include <stdlib.h>
#include <limits.h>
#include "twostacks.h"

void init(twostacks *sp, int size_a, int size_b) {
    sp -> a = (int*)malloc(sizeof(int) * (size_a + size_b));
    sp -> b = sp -> a + size_a;
    sp -> size_a = size_a;
    sp -> size_b = size_b;
    sp -> top_a = -1;
    sp -> top_b = -1;
}

void push1(twostacks *sp, int val) {
    if(sp -> top_a == sp -> size_a - 1)
        return;
    sp -> a[++sp -> top_a] = val;
    return;
}

void push2(twostacks *sp, int val) {
    if(sp -> top_b == sp -> size_b - 1)
        return;
    sp -> b[++sp -> top_b] = val;
    return;
}

int pop1(twostacks *sp) {
    if(sp -> top_a == -1)
        return INT_MIN;
    return sp -> a[sp -> top_a--];
}

int pop2(twostacks *sp) {
    if(sp -> top_b == -1)
        return INT_MIN;
    return sp -> b[sp -> top_b--];
}