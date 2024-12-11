#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"

void init_hashmap(hashmap *hp, int size) {
    hp -> table = (entry *)malloc(sizeof(entry) * size);
    hp -> size = size;
    return;
}

int division_hash(int key, int size) {
    return key % size;
}

int multiplication_hash(int key, int size) {
    double A = 0.6180339887; // Fractional part of the golden ratio
    double frac = (key * A) - (int)(key * A);
    return (int)(frac * size);
}

int universal_hash(int key, int size, int a, int b, int p) {
    return ((a * key + b) % p) % size;
}

void division_insert(hashmap *hp, int key, int value) {
    int hash = division_hash(key, hp -> size);
    hp -> table[hash].key = key;
    hp -> table[hash].value = value;
    printf("Key %d inserted at index %d\n", key, hash);
    return;
}

void multiplication_insert(hashmap *hp, int key, int value) {
    int hash = multiplication_hash(key, hp -> size);
    hp -> table[hash].key = key;
    hp -> table[hash].value = value;
    printf("Key %d inserted at index %d\n", key, hash);
    return;
}

void universal_insert(hashmap *hp, int key, int value) {
    //Values for coefficient, offset and prime are predefined
    int coeff = 100;
    int offset = 200;
    int prime = 10007; //Prime number larger than largest possible key

    int hash = universal_hash(key, hp -> size, coeff, offset, prime);
    hp -> table[hash].key = key;
    hp -> table[hash].value = value;
    printf("Key %d inserted at index %d\n", key, hash);
    return;
}
