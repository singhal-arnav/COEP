typedef struct node {
    int data;
    struct node* next;
}node;

typedef node* CLL;

void init_CLL(CLL *lp);
void insert_beg(CLL *lp, int val);
void insert_end(CLL *lp, int val);
void insert_pos(CLL *lp, int pos, int val);
int is_empty(CLL l);
void remove_beg(CLL *lp);
void remove_end(CLL *lp);
void remove_pos(CLL *lp, int pos);
void sort(CLL *lp);
void display(CLL l);