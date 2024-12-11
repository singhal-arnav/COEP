#include <stdio.h>
#include <stdlib.h>
#include "hashmap.h"

void init_hashmap(hashmap *hp, int size) {
    hp -> table = (entry **)malloc(sizeof(entry *) * size);
    hp -> size = size;
    for(int i = 0; i < size; i++)
        hp -> table[i] = NULL;
    return;
}

int hash(int key, int size) {
    return key % size;
}

void insert(hashmap *hp, int key, int value) {
    entry *e = (entry *)malloc(sizeof(entry));
    e -> key = key;
    e -> value = value;
    e -> next = NULL;

    int index = hash(key, hp -> size);
    printf("Attempting to insert key %d at index %d\n", key, index);
    if(hp -> table[index]) {
        printf("Collision has occurred\n");
        e -> next = hp -> table[index];
    }
    hp -> table[index] = e;
    printf("Key %d successfully inserted at index %d using chaining\n", key, index);
    
    printf("Entries at index %d:\n", index);
    while(e -> next) {
        printf("(%d, %d) -> ", e -> key, e -> value);
        e = e -> next;
    }
    printf("(%d, %d)\n", e -> key, e -> value);

    return;
}