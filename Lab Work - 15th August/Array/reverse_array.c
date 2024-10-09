#include <stdio.h>

int main() {
    int a[] = {10, 45, 3216, 88}, li, ui, temp;
    int n = sizeof(a)/sizeof(a[0]);
    li = 0;
    ui = n - 1;
    while(li < ui) {
        temp = a[li];
        a[li] = a[ui];
        a[ui] = temp;
        li++;
        ui--;
    }
    printf("{");
    for(int i = 0; i < n - 1; i++)
        printf("%d, ", a[i]);
    printf("%d}", a[n - 1]);
    return 0;
}