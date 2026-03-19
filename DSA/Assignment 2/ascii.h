#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev, *next;
}node;

typedef struct ASCII {
    node *front, *rear;
}ASCII;

void init_ASCII(ASCII* L);
int isempty(ASCII L);
void insert_at_beg(ASCII* L, int num);
void ASCII_of(ASCII* L, char c);
void traverse(ASCII L);
void Destroy(ASCII* L);
