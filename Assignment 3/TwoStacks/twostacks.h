typedef struct twostacks {
    int *a;
    int *b;
    int size_a;
    int size_b;
    int top_a;
    int top_b;
}twostacks;

void init(twostacks *sp, int size_a, int size_b);
void push1(twostacks *sp, int val);
void push2(twostacks *sp, int val);
int pop1(twostacks *sp);
int pop2(twostacks *sp);