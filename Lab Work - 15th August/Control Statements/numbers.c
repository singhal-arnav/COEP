#include <stdio.h>

int main() {
    int a[10];
    printf("Enter 10 integers:\n");
    for(int i = 0; i < 10; i++)
        scanf("%d", &a[i]);
    for(int i = 0; i < 9; i++)
        printf("%d, ", a[i]);
    printf("%d", a[9]);
    return 0;
}