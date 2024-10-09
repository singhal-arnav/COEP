#include <stdio.h>

int main() {
    int a, b, c;
    printf("Enter the length of the first side: ");
    scanf("%d", &a);
    printf("Enter the length of the second side: ");
    scanf("%d", &b);
    printf("Enter the length of the third side: ");
    scanf("%d", &c);
    
    if(a == b && b == c)
        printf("Equilateral triangle");
    else if(a == b || b == c || c == a)
        printf("Isosceles triangle");
    else
        printf("Scalene triangle");
    return 0;
}