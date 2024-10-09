#include <stdio.h>
#include <string.h>
#include <limits.h>

int str_to_int(char* str) {
    int flag = 0, num = 0, i;
    for(i = 0; i < strlen(str); i++) {
        char ch = str[i];
        if(ch >= 48 && ch <= 57) {
            num *= 10;
            num += ch - 48;
        }
        else {
            flag = 1;
            break;
        }
    }
    if(flag)
        return INT_MIN;
    return num;
}

int main() {
    char s[] = "165";

    printf("Given string: %s\n", s);
    int n = str_to_int(s);
    if(n == INT_MIN)
        printf("String does not contain only digits. It cannot be represented as an integer.");
    else
        printf("Integer representation: %d", n);

    return 0;
}