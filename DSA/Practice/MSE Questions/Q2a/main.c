#include <stdio.h>
#include "array.h"

int main() {
    array a;

    init(&a);

    append(&a, 3);
    append(&a, -5);
    append(&a, 20);
    append(&a, -10);
    append(&a, -100);

    traverse(a);

    mov_neg(&a);

    traverse(a);
    
    return 0;
}