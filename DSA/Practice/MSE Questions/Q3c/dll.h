typedef struct node {
    int data;
    struct node *prev, *next;
}node;

typedef node *dll;

void init(dll *lp);
void append(dll *lp, int val);
int count(dll l);