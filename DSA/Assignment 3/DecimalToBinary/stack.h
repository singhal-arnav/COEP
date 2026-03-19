typedef struct node {
    int data;
    struct node *next;
}node;

typedef struct stack {
    node *top;
}stack;

void init(stack *sp);
void push(stack *sp, int val);
int is_empty(stack s);
int pop(stack *sp);
int dec_to_bin(int num);