#include <stdio.h>

void bubble_sort(int *a, int size) {
    int i, j, temp;

    for(i = 0; i < size - 1; i++) {
        for(j = 0; j < size - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return;
}

int main() {
    int a[] = {5, 4, 3, 2, 1}, size = 5;

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    bubble_sort(a, size);

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}