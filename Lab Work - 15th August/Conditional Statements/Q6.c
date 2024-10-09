#include <stdio.h>

int main() {
    char c;
    printf("Enter a character: ");
    scanf("%c", &c);

    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        printf("The character is an alphabet");
    else
        printf("The character is not an alphabet");
    
    return 0;
}