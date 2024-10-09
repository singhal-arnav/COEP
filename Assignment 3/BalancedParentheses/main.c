#include <stdio.h>
#include "stack.c"
#define MAX_SIZE 100

int main() {
    char exp[MAX_SIZE];

    printf("Enter the expression: ");
    scanf("%s", exp);

    if(check_exp(exp))
        printf("True\n");
    else
        printf("False\n");  

    return 0;
}