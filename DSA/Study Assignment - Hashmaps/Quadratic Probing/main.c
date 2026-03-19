#include <stdio.h>
#include "hashmap.h"

int main() {
    hashmap h;

    init_hashmap(&h, 23);

    insert(&h, 1, 5);
    insert(&h, 24, 10);
    insert(&h, 40, 20);
    insert(&h, 47, 100);

    return 0;
}