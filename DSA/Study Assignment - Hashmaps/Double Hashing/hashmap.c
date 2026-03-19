#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"

void init_hashmap(hashmap *hp, int size) {
    hp->table = (entry *)malloc(sizeof(entry) * size);
    hp->size = size;
    for (int i = 0; i < size; i++)
        hp->table[i].key = hp->table[i].value = INT_MIN;
    return;
}

//Primary hash function
int primary_hash(int key, int size) {
    return key % size;
}

//Secondary hash function
int secondary_hash(int key, int size) {
    return 1 + (key % (size - 1));
}

void insert(hashmap *hp, int key, int value) {
    int index = primary_hash(key, hp->size);
    int step = secondary_hash(key, hp->size);
    int i = 0;

    printf("Attempting to insert key %d at index %d\n", key, index);

    while (hp->table[index].key != INT_MIN && i < hp->size) {
        printf("Collision has occurred at index %d\n", index);
        index = (index + step) % hp->size;
        i++;
        printf("Attempting to insert key %d at new index %d\n", key, index);
    }

    if (i == hp->size) {
        printf("Hashmap is full. Key %d could not be inserted.\n", key);
        return;
    }

    hp->table[index].key = key;
    hp->table[index].value = value;
    printf("Key %d successfully inserted at index %d\n", key, index);
    return;
}
