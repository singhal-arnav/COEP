typedef struct node {
    int data;
    struct node *prev, *next;
}node;

typedef struct list {
    node *front, *rear;
}list;

void init(list *lp);
int is_empty(list l);
void append(list *lp, int val);
void display(list l);
void insert_at_pos(list *lp, int ind, int val);