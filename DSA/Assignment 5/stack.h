typedef struct stacknode {
    struct node *data;
    struct stacknode *next;
}stacknode;

typedef struct stack {
    stacknode *top;
}stack;

void initStack(stack *sp);
void push(stack *sp, struct node *n);
int isEmpty(stack s);
struct node* pop(stack *sp);