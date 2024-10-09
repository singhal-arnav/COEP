#include <stdio.h>

int main() {
    char ch;
    printf("Enter a character: ");
    scanf("%c", &ch);

    if(ch >= 65 && ch <= 90)
        printf("The entered character is an uppercase alphabet");
    else if(ch >= 97 && ch <= 122)
        printf("The entered character is a lowercase alphabet");
    else
        printf("The entered character is not an alphabet");
    
    return 0;
}