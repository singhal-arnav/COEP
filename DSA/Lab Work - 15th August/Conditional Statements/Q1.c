#include <stdio.h>

int main() {
    int a, b;
    printf("Enter the first number: ");
    scanf("%d", &a);
    printf("Enter the second number: ");
    scanf("%d", &b);
    
    if(a > b)
        printf("Maximum = %d", a);
    else
        printf("Maximum = %d", b);

    return 0;
}