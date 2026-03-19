typedef struct stack {
    char *a;
    int size;
    int top;
}stack;

void init(stack *sp, int size);
int isEmpty(stack s);
void push(stack *sp, char c);
char pop(stack *sp);
char peek(stack s);
int check_exp(char *str);