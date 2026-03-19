#include <stdio.h>
#include "hashmap.h"

int main() {
    hashmap h1, h2, h3;

    init_hashmap(&h1, 23);
    printf("Inserting values using division method:\n");
    division_insert(&h1, 101, 50);
    division_insert(&h1, 200, 40);
    division_insert(&h1, 70, 30);
    
    init_hashmap(&h2, 23);
    printf("Inserting values using multiplication method:\n");
    multiplication_insert(&h2, 101, 50);
    multiplication_insert(&h2, 200, 40);
    multiplication_insert(&h2, 70, 30);

    init_hashmap(&h3, 23);
    printf("Inserting values using universal method:\n");
    universal_insert(&h3, 101, 50);
    universal_insert(&h3, 200, 40);
    universal_insert(&h3, 70, 30);

    return 0;
}