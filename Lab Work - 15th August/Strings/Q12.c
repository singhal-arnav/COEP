#include <stdio.h>
#include <string.h>

void rev(char* str) {
    int i = 0, len = strlen(str);
    char temp;
    while(i <= len/2 - 1) {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
        i++;
    }
    return;
}

int main() {
    char s[] = "data structures and algorithms";
    printf("Original string: %s\n", s);
    rev(s);
    printf("Reversed string: %s", s);

    return 0;
}