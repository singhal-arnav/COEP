#include <stdio.h>

int main() {
    char c;
    printf("Enter an alphabet: ");
    scanf("%c", &c);

    if(c >= 97 && c <= 122)
        c -= 32;
    
    if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        printf("The entered alphabet is a vowel");
    else
        printf("The entered alphabet is a consonant");
    
    return 0;
}