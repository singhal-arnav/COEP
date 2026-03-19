#include <stdio.h>

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int partition(int *a, int low, int high) {
    int p = a[low], i = low + 1, j = high;
    while(i < j) {
        while(a[i] <= p && i <= high - 1)
            i++;
        while(a[j] > p && j >= low + 1)
            j--;
        if(i < j) {
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[low], &a[j]);
    return j;
}

void quick_sort(int *a, int low, int high) {
    if(low < high) {
        int pi = partition(a, low, high);
        quick_sort(a, low, pi - 1);
        quick_sort(a, pi + 1, high);
    }
    return;
}

int main() {
    int a[] = {5, 4, 1, 3, 2, 1}, size = 6;

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    quick_sort(a, 0, size - 1);

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}