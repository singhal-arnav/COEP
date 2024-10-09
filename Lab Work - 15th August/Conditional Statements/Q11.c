#include <stdio.h>

int main() {
    int a, b, c;
    printf("Enter the angles of the triangle:\n");
    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    if((a + b + c) == 180)
        printf("The triangle is valid");
    else
        printf("The triangle is invalid");
    
    return 0;
}