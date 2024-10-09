typedef struct stack {
    char *a;
    int size;
    int top;
}stack;

void init(stack *sp, int size);
int isFull(stack s);
int isEmpty(stack s);
void push(stack *sp, char c);
char pop(stack *sp);
void reverse_string(char *str);