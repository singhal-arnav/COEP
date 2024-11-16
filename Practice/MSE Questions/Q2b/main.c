#include <stdio.h>
#include "array.h"

int main() {
    array a;

    init(&a);

    append(&a, 3);
    append(&a, 40);
    append(&a, 10);
    append(&a, 3);
    append(&a, 20);
    append(&a, 3);

    traverse(a);

    mov_freq(&a);

    traverse(a);
    
    return 0;
}