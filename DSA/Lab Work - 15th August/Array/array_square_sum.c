#include <stdio.h>

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, sum = 0;
    for(int i = 0; i < 10; i++) {
        sum += (a[i] * a[i]);
    }
    printf("Sum of squares of the elements = %d", sum);
    return 0;
}