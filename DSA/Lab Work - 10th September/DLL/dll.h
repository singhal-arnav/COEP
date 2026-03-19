typedef struct node {
    int data;
    struct node *prev, *next;
}node;

typedef struct DLL {
    node *front, *rear;
}DLL;

void init_DLL(DLL *lp);
int is_empty(DLL l);
void insert_beg(DLL *lp, int val);
void insert_end(DLL *lp, int val);
void insert_pos(DLL *lp, int pos, int val);
void remove_beg(DLL *lp);
void remove_end(DLL *lp);
void remove_pos(DLL *lp, int pos);
void sort(DLL *lp);
void displayRL(DLL l);
void displayLR(DLL l);
int is_palindrome(DLL l);
void remove_duplicates(DLL *lp);