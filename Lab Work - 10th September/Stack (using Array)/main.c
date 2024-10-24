#include <stdio.h>
#include "stack.c"

int main() {
    stack s;
    init(&s, 10);
    
    int item;
    while(scanf("%d", &item) != EOF)
        push(&s, item);
    
    if((item = peek(s)) != INT_MIN) {
        printf("Top element of the stack: %d\n", item);
        printf("Popping and displaying contents of stack:\n");
        while((item = pop(&s))!= INT_MIN)
            printf("%d\n", item);
    }
    else
        printf("The stack is empty\n");
    
    return 0;
}

