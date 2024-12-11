#include <stdio.h>

void insertion_sort(int *a, int size) {
    int i, j, current;

    for(i = 1; i < size; i++) {
        current = a[i];
        j = i - 1;

        while(j >= 0 && a[j] > current) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = current;
    }
}

int main() {
    int a[] = {5, 4, 1, 3, 2, 1}, size = 6;

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    insertion_sort(a, size);

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}