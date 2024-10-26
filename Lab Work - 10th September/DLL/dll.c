#include "DLL.h"
#include <stdio.h>
#include <stdlib.h>

void init_DLL(DLL *lp) {
    lp -> front = NULL;
    lp -> rear = NULL;
}

int is_empty(DLL l) {
    if(l.front == NULL)
        return 1;
    return 0;
}

void insert_beg(DLL *lp, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> data = val;
    nn -> prev = NULL;
    nn -> next = lp -> front;

    if(!is_empty(*lp))
        lp -> front -> prev = nn;
    else
        lp -> rear = nn;
    lp -> front = nn;

    return;
}

void insert_end(DLL *lp, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> data = val;
    nn -> next = NULL;
    nn -> prev = lp -> rear;
    
    if(!is_empty(*lp)) {
        lp -> rear -> next = nn;
        lp -> rear = nn;
    }
    else {
        lp -> front = nn;
        lp -> rear = nn;
    }

    return;
}

void insert_pos(DLL *lp, int pos, int val) {
    node *nn = (node*)malloc(sizeof(node));
    nn -> data = val;

    if(is_empty(*lp)) {
        lp -> front = lp -> rear = nn;
        nn -> prev = nn -> next = NULL;
    }
    else {
        node *p = lp -> front;

        for(int i = 0; i < pos - 1; i++)
            p = p -> next;

        nn -> prev = p;
        nn -> next = p -> next;
        
        if(p -> next)
            p -> next -> prev = nn;
        p -> next = nn;
    }

    return;
}

void remove_beg(DLL *lp) {
    if(is_empty(*lp))
        return;
    
    node *p = lp -> front;

    if(lp -> front -> next == NULL) {
        lp -> front = NULL;
        lp -> rear = NULL;
    }
    else {
        lp -> front = lp -> front -> next;
        lp -> front -> prev = NULL;
    }

    free(p);
    return;
}

void remove_end(DLL *lp) {
    if(is_empty(*lp))
        return;
    
    node *p = lp -> rear;

    if(lp -> rear -> prev == NULL) {
        lp -> front = NULL;
        lp -> rear = NULL;
    }
    else {
        lp -> rear = lp -> rear -> prev;
        lp -> rear -> next = NULL;
    }

    free(p);
    return;
}

void remove_pos(DLL *lp, int pos) {
    if(is_empty(*lp))
        return;

    node *p = lp -> front;

    for(int i = 0; i < pos; i++)
        p = p -> next;
    
    if(lp -> front == p)
        lp -> front = p -> next;
    if(lp -> rear == p)
        lp -> rear = p -> prev;
    if(p -> next)
        p -> next -> prev = p -> prev;
    if(p -> prev)
        p -> prev -> next = p -> next;

    free(p);

    return;
}

void sort(DLL *lp) {
    node *p1 = lp -> front;
 	node *temp = NULL;
 	int x;
 	if(!p1)
	   return;
 	node *p2 = p1->next;
 	while(p2){
        temp = p1;  
        x = p2 -> data;
        while(temp && temp -> data > x){
            temp -> next -> data = temp -> data;
            temp = temp -> prev;
        }
        if(!temp)
            lp -> front -> data = x; 
    
        else
            temp -> next -> data = x;
        p2 = p2 -> next;
        p1 = p1 -> next;
	}
    return;
}

void displayRL(DLL l) {
    node *p;
    printf("Right to Left: [ ");
    p = l.rear;
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%d ", p->data);
        p = p->prev;
    }while(p != NULL);
    printf("]\n");
    return;
}

void displayLR(DLL l) {
    node *p;
    printf("Left to Right: [ ");
    p = l.front;
    if(!p) {
        printf("]\n");
        return;
    }
    do {
        printf("%d ", p->data);
        p = p->next;
    }while(p != NULL);
    printf("]\n");
    return;
}

int is_palindrome(DLL l) {
    node *p = l.front;
    node *q = l.rear;

    while(p != q && p != q -> next) {
        if(p -> data != q -> data)
            return 0;
        else {
            p = p -> next;
            q = q -> prev;
        }
    }

    return 1;
}

void remove_duplicates(DLL *lp) {
    node *p = lp -> front;
    int i = 0;

    while(p) {
        node *q = p -> next;
        int j = i + 1;
        while(q) {
            q = q -> next;
            if(q -> data == p -> data)
                remove_pos(lp, j);
            else
                j++;
        }
        p = p -> next;
    }
}