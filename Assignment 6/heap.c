#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

void init_heap(heap *h1, int size){  
    h1->h = (int *)malloc(sizeof(int) * size);
    h1->rear = -1;
    h1->size = size;
    return;
}

int parent(int index){       
    return ((index-1)/2);
}

void swaph(heap *h1, int a, int b){ 
    if(a>=h1->size || b >=h1->size)
        return;
    else{
        int k=h1->h[a];
        h1->h[a]=h1->h[b];
        h1->h[b]=k;
        return;
    }
    return;
}
void insert_heap(heap *h1, int k){
    if(h1->rear == h1->size-1)
        return;
    h1->rear++;
    h1->h[h1->rear]=k;
    int i=h1->rear;
    while(i > 0 && h1->h[i] > h1->h[parent(i)]){
        swaph(h1, i, parent(i));
        i=parent(i);
    }
    return;
}
void print_heap(heap h1){       
    for(int i=0; i<=h1.rear; i++){
        printf("%d\t", h1.h[i]);
        
    }
    printf("\n");
    return;
}
void heapify(heap *h1){          //Heapify using top down approch
    if(h1->rear==0 || h1->rear==-1)
        return;
    int j=0;
    while(j <=(h1->rear)){
        int lchild=2*j+1;
        int rchild=2*j+2;
        if(lchild > h1->rear)
            return;
        if(rchild > h1->rear){
            if(h1->h[j] < h1->h[lchild]){
                swaph(h1, j, lchild);
            }
            return;
        }
        if((h1->h[j] > h1->h[lchild]) && (h1->h[j] > h1->h[rchild]))
            return;
        if(h1->h[lchild] > h1->h[rchild]){
            swaph(h1, j, lchild);
            j=lchild;
        }
        else{
            swaph(h1, j, rchild);
            j=rchild;
        }
    }
}

void heap_sort(heap *h1){
    int k=h1->rear;
    if(h1->rear==-1)
        return;
    for(int i=h1->rear; i>0; i--){
        swaph(h1,i,0);
        h1->rear--;
        heapify(h1);
    }
    h1->rear=k;
    print_heap(*h1);
    return;
}