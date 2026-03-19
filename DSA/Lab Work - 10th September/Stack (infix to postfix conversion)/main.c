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
