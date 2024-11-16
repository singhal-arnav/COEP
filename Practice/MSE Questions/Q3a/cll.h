typedef struct node {
    int data;
    struct node *next;
}node;

typedef node* cll;

void init_CLL(cll *lp);
void insert_beg(cll *lp, int val);
void traverse(cll l);
void del_odd(cll *lp);