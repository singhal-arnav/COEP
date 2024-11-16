#include <stdio.h>
#include "dll.h"

int main() {
    dll l;

    init(&l);

    append(&l, 3);
    append(&l, 5);
    append(&l, 5);

    printf("Length of list = %d\n", count(l));

    return 0;
}