#include <stdio.h>

int linear_search(int *arr, int size, int val) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == val)
            return i;
    }
    return -1;
}

int main() {
    int a[] = {1, 2, 3, 4, 5}, ind;

    ind = linear_search(a, 5, 4);
    if(ind != -1)
        printf("Element found at index %d\n", ind);
    else
        printf("Element not found\n");
    
    return 0;
}