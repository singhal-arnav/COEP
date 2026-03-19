#include <stdio.h>
#include <string.h>

char* strtok(char* str, const char* delim) {
    static char* last = NULL;  // Static pointer to store the rest of the string between calls
    if (str == NULL) {
        str = last;
        if (str == NULL)
            return NULL;
    }
    
    int inc = 0;
    str += strspn(str, delim);
    
    if (*str == '\0') {
        last = NULL;
        return NULL;
    }

    char* end = str + strcspn(str, delim);

    if (*end != '\0') {
        *end = '\0';
        last = end + 1;
    } else {
        last = NULL;
    }

    return str;
}

int main() {
    char str[] = "data,structures,,and algorithms";
    char* token = strtok(str, ", ");
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, ", ");
    }
    return 0;
}
