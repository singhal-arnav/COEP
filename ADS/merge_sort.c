#include <stdio.h>

#define SIZE 20

void printArray(int arr[], int left, int right) {
    printf("[");
    for (int i = left; i <= right; i++) {
        printf("%d", arr[i]);
        if (i < right) printf(" ");
    }
    printf("]\n");
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    printf("Clubbing: ");
    printArray(arr, l, r);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;

        printf("Dividing: ");
        printArray(arr, l, r);

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    int arr[SIZE] = {38, 27, 43, 3, 9, 82, 10, 95, 11, 56,
                     72, 14, 67, 20, 33, 45, 1, 8, 19, 60};

    printf("Original array:\n");
    printArray(arr, 0, SIZE - 1);

    mergeSort(arr, 0, SIZE - 1);

    printf("\nSorted array:\n");
    printArray(arr, 0, SIZE - 1);

    return 0;
}
