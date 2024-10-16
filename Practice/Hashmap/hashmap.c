#include <string.h>
#include <stdio.h>
#include "hashmap.h"

void init_table(hashmap h) {
    int i;
    for(i = 0; i < MAX_TABLE_SIZE; i++)
        h[i].key[0] = '\0';
}

int transform(char *key) {
    int number = 0;
    while(*key)
        number += *key++;
    return number;
}

int hash(char *key) {
    return (transform(key) % MAX_TABLE_SIZE);
}

void linear_insert(element item, hashmap h) {
    int i, hash_value;
    hash_value = hash(item.key);
    i = hash_value;
    while(strlen(h[i].key)) {
        if(!strcmp(h[i].key, item.key)) {
            printf("Duplicate entry\n");
            return;
        }
        i = (i + 1) % MAX_TABLE_SIZE;
        if(i == hash_value) {
            printf("The table is full\n");
            return;
        }
    }
    h[i] = item;
    return;
}