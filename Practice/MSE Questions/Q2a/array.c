#include <stdio.h>
#include <stdlib.h>
#include "array.h"

void init(array *ap) {
    ap -> A = (int*) malloc(sizeof(int) * 20);
    ap -> size = 20;
    ap -> len = 0;
    return;
}

void append(array *ap, int val) {
    if(ap -> len < ap -> size)
        ap -> A[(ap -> len)++] = val;
    return;
}

void traverse(array a) {
    for(int i = 0; i < a.len; i++)
        printf("%d ", a.A[i]);
    printf("\n");
    return;
}

void mov_neg(array *ap) {
    int i = 0, temp;
    while(i < ap -> len) {
        if(ap -> A[i] < 0) {
            while(i > 0 && ap -> A[i - 1] >= 0) {
                temp = ap -> A[i];
                ap -> A[i] = ap -> A[i - 1];
                ap -> A[i - 1] = temp;
                i--;
            }
        }
        i++;
    }
    return;
}