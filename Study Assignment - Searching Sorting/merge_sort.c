#include <stdio.h>

void merge(int *a, int low, int mid, int high) {
    int i, j, k;
    int n1 = mid - low + 1, n2 = high - mid;
    int left_arr[n1], right_arr[n2];

    for(i = 0; i < n1; i++)
        left_arr[i] = a[low + i];
    for(j = 0; j < n2; j++)
        right_arr[j] = a[mid + j + 1];
    
    i = j = 0;
    k = low;
    while(i < n1 && j < n2) {
        if(left_arr[i] <= right_arr[j]) {
            a[k] = left_arr[i];
            i++;
        }
        else {
            a[k] = right_arr[j];
            j++;
        }
        k++;
    }

    while(i < n1) {
        a[k] = left_arr[i];
        i++;
        k++;
    }

    while(j < n2) {
        a[k] = right_arr[j];
        j++;
        k++;
    }
    
    return;
}

void merge_sort(int *a, int low, int high) {
    if(low == high)
        return;
    
    int mid = (low + high) / 2;
    merge_sort(a, low, mid);
    merge_sort(a, mid + 1, high);
    merge(a, low, mid, high);
    return;
}

int main() {
    int a[] = {5, 4, 1, 3, 2, 1}, size = 6;

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    merge_sort(a, 0, size - 1);

    for(int i = 0; i < size; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}