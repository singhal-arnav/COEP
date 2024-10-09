#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* cutonchar(char* str, char ch) {
    int i = 0, n = strlen(str);
    char* new_str = (char*)malloc(n * sizeof(char)); //creating new string so that original string is not modified
    while(str[i] != ch && i < n) {
        new_str[i] = str[i];
        i++;
    }
    new_str[i] = '\0';
    return new_str;
}

int main() {
    char s[] = "DSA is an interesting course";

    printf("Original string: %s\n", s);
    printf("Modified string: %s", cutonchar(s, 'i'));

    return 0;
}