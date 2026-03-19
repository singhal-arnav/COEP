#include <stdio.h>

void selection_sort(int *a, int size) {
    int i, j, temp, min;

    for(i = 0; i < size - 1; i++) {
        min = i;
        for(j = i + 1; j < size; j++) {
            if(a[j] < a[min])
                min = j;
        }
        if(min != i) {
            temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
    return;
}

int main() {
    int a[] = {5, 4, 1, 3, 2, 1}, size = 6;

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    selection_sort(a, size);

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}