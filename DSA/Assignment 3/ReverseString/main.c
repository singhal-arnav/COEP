#include <stdio.h>
#include "stack.c"

int main() {
    char s[] = "Data Structures and Algorithms";
    printf("Original string: %s\n", s);
    reverse_string(s);
    printf("Reversed string: %s\n", s);

    return 0;
}