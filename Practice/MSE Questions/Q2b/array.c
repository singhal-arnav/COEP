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

void mov_freq(array *ap) {
    int max_count = 0;
    int most_common = ap->A[0];
    
    for (int i = 0; i < ap->len; i++) {
        int count = 0;
        for (int j = 0; j < ap->len; j++) {
            if (ap->A[i] == ap->A[j]) {
                count++;
            }
        }
        if (count > max_count) {
            max_count = count;
            most_common = ap->A[i];
        }
    }

    int i = 0, temp;
    while(i < ap -> len) {
        if(ap -> A[i] == most_common) {
            while(i > 0 && ap -> A[i - 1] != most_common) {
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