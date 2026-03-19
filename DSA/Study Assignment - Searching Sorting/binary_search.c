#include <stdio.h>

int binary_search(int *arr, int size, int val) {
    int mid, low = 0, high = size - 1;
    while(low <= high) {
        mid = (low + high)/2;
        if(val == arr[mid])
            return mid;
        else if(val < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main() {
    int a[] = {1, 2, 3, 4, 5}, ind;

    ind = binary_search(a, 5, 4);
    if(ind != -1)
        printf("Element found at index %d\n", ind);
    else
        printf("Element not found\n");
    
    return 0;
}