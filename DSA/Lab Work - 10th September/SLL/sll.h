typedef struct node {
    int data;
    struct node* next;
}node;

typedef node* SLL;

void init_SLL(SLL *lp);
void append(SLL* lp, int val);
void traverse(SLL l);
void insert_at_beg(SLL *lp, int val);
void remove_at_pos(SLL *lp, int pos);
int len(SLL l);