#include <stdio.h>

int count(char* str, char c) {
    int i = 0, occ = 0;
    while(str[i] != '\0') {
        if(str[i] == c)
            occ++;
        i++;
    }
    return occ;
}

int main() {
    char str[] = "data structures and algorithms", ch;
    printf("Enter the character for which the no of occurrences is to be found: ");
    scanf("%c", &ch);
    printf("Number of occurences of \'%c\' is %d", ch, count(str, ch));
    return 0;
}