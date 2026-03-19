#include <stdio.h>
#include <stdlib.h>

#include "polynomial.h"

void init_poly(poly* p, int n){
	p -> n = n;
	p -> size = 0;
	p -> t = (term*) malloc(sizeof(term) * n);
	return;
}

void append(poly* p, int coeff, int exp){
	p -> t[p -> size].coeff = coeff;
	p -> t[p -> size].exp = exp;
	p -> size++;
	return;
}

void display(poly p){
	int i, flag = 1;
	for (i = 0; i < p.size; i++){
		if(p.t[i].coeff == 0)
			continue;
		else {
			flag = 0;
			if(p.t[i].coeff > 0)
				printf(" %c %d", (i) ? '+' : ' ', p.t[i].coeff);
			else
				printf(" - %d", -p.t[i].coeff);
		}
		
		if(p.t[i].exp == 1)
			printf("x");
		else if(p.t[i].exp)
			printf("x^%d", p.t[i].exp);
	}

	if(flag)
		printf("%d", 0);

	printf("\n");
	return;
}

void add_poly(poly* p1, poly* p2, poly* res) {
	for(int i = 0; i < p1->size; i++) {
		append(res, p1->t[i].coeff, p1->t[i].exp);
	}

	for(int i = 0; i < p2->size; i++) {
		int flag = 1;
		for(int j = 0; j < res->size; j++) {
			if(res->t[j].exp == p2->t[i].exp) {
				res->t[j].coeff += p2->t[i].coeff;
				flag = 0;
				break;
			}
		}
		if(flag)
			append(res, p2->t[i].coeff, p2->t[i].exp);
	}

	return;
}

void sub_poly(poly* p1, poly* p2, poly* res) {
	for(int i = 0; i < p1->size; i++) {
		append(res, p1->t[i].coeff, p1->t[i].exp);
	}

	for(int i = 0; i < p2->size; i++) {
		int flag = 1;
		for(int j = 0; j < res->size; j++) {
			if(res->t[j].exp == p2->t[i].exp) {
				res->t[j].coeff -= p2->t[i].coeff;
				flag = 0;
				break;
			}
		}
		if(flag)
			append(res, -(p2->t[i].coeff), p2->t[i].exp);
	}

	return;
}