#include <stdio.h>
#include "twostacks.c"

int main() {
    twostacks s;
    
    init(&s, 2, 3);

    push1(&s, 2);
    push2(&s, 3);
    push2(&s, 4);
    printf("%d\n", pop1(&s));
    push1(&s, pop2(&s));
    printf("%d\n", pop1(&s));
    printf("%d\n", pop2(&s));

    return 0;
}