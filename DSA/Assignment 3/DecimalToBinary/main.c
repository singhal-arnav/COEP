#include <stdio.h>
#include "stack.c"

int main() {
    int n;

    printf("Enter a decimal number: ");
    scanf("%d", &n);
    printf("Base 2 (binary) equivalent = %d", dec_to_bin(n));

    return 0;
}