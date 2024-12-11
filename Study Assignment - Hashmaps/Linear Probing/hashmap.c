#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "hashmap.h"

void init_hashmap(hashmap *hp, int size) {
    hp->table = (entry *)malloc(sizeof(entry) * size);
    hp->size = size;
    for (int i = 0; i < size; i++)
        hp->table[i].key = hp->table[i].value = INT_MIN;
}

int hash(int key, int size) {
    return key % size;
}

void insert(hashmap *hp, int key, int value) {
    int index = hash(key, hp->size);
    int original_index = index;
    int probes = 0;

    printf("Attempting to insert key %d at index %d\n", key, index);

    while (hp->table[index].key != INT_MIN) {
        printf("Collision has occurred at index %d\n", index);
        index = (index + 1) % hp->size;
        probes++;
        printf("Attempting to insert key %d at new index %d\n", key, index);

        if (index == original_index) {
            printf("Hashmap is full. Key %d could not be inserted.\n", key);
            return;
        }
    }

    hp->table[index].key = key;
    hp->table[index].value = value;
    printf("Key %d successfully inserted at index %d. Probes required: %d\n", key, index, probes);
}
