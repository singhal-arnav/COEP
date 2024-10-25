/*
Algorithm to convert infix expression to postfix
1. Declare a char Stack and initialize it
2. Read the infix expression from L-R char by char
3. if operand is encountered - append it to output string
4. if '(' is encountered - push it in the stack
5. if ')' pop all characters and appeend to output string till
    ')' is encountered. DO not append ')'
6. if operator is encountered pop all operators of higher or equal precedence and append to o/p
    or till stack is not empty or ')' is encountered. drop ')'
7. push the operator of step 6.
8  repeat 2 - 6 till end of expression
9 pop all characters and append.
*/

#include <stdio.h>
#include <ctype.h>
#include "stack.c"

int precedence(char c){
    if(c == '+')
        return 10;
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    return 0;
}

int main() {
    char E[50];
    gets(E);
    stack s;
    init(&s, 50);

    char postfix[50], c;
    int i = 0, j = 0;

    while(E[i]!= '\0') {
        c = E[i];
        if(isdigit(c)) {
            postfix[j++] = c ;
            if(!isdigit(E[i + 1]))
                postfix[j++] = ' ';
        }
        else if(c == '(')
            push(&s, '(');
        else if(c == ')') {
            while(!isEmpty(s) && peek(s)!= '('){
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            if(peek(s) == '(')
                pop(&s);
        }
        else {
            if(c == '+' || c =='-' || c == '*'|| c == '/') {
                if(isEmpty(s))
                    push(&s, c);
                else {
                    while(!isEmpty(s) && precedence(peek(s)) >= precedence(c)){
                        postfix[j++] = pop(&s);
                        postfix[j++] = ' ';
                    }
                    push(&s, c);
                }
            }
        }
        i++;
    }

    while(!isEmpty(s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }
    
    for(i = 0; i < j; i++)
          printf("%c", postfix[i]);
    
    return 0;
}
