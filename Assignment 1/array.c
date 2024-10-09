#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "array.h"

void init(array* a, int size){
	a -> size = size;
	a -> len = 0;
	a -> A = (int*) malloc(sizeof(int) * size);
	return;
}

int is_empty(array* a){
	return a -> len == 0;
}

int is_full(array* a){
	return a -> size == a -> len; 
}

void append(array* a,int data){
	if(is_full(a)){
		return;
	}
	a -> A[a -> len++] = data;
	return;
}

void insert_at_index(array* a, int idx, int data){
	if(is_full(a)){
		return;
	}
	for(int i = a->len; i >= idx; i--){
		a -> A[i + 1] = a -> A[i];
	}
	a -> A[idx] = data;
	a -> len++;
	return;
}

void remove_at_index(array* a, int idx){
	if (is_empty(a)){
		return;
	}
	for(int i=idx; i < a->len; i++){
		a->A[i] = a->A[i+1];
	}
	a -> size--;
	return;
}

void display(array* a){
	if (is_empty(a)){
		return;
	}
	for (int i = 0; i < a->len; i++){
		printf("%d ", a->A[i]);
	}
	printf("\n");
	return;
}

int max(array* a){
	if (is_empty(a)){
		return INT_MIN;
	}
	int ans = INT_MIN;
	for (int i=0; i < a->len; i++){
		if(ans < a -> A[i]){
			ans = a -> A[i];
		}
	}
	return ans;
}

int min(array* a){
        if (is_empty(a)){
                return INT_MIN;
        }
        int ans = INT_MAX;
        for (int i = 0; i < a->len; i++){
                if (ans > a->A[i]){
                        ans = a -> A[i];
                }
        }
        return ans;
}


void reverse(array* a){
	if (is_empty(a)){
		return;
	}
	int start = 0;
	int end = a->len - 1;
	while(start < end){
		int temp = a->A[start];
		a->A[start] = a->A[end];
		a->A[end] = temp;
		start++;
		end--;
	}
	return;
}

void merge(array* a1, array* a2, array* res){
	
	for (int i = 0; i < a1->len; i++){
		res->A[i] = a1->A[i];
		res->len++;
	}
	for (int j = 0; j < a2->len; j++){
		res->A[res->len++] = a2->A[j];
	}
}