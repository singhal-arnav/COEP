#include <stdio.h>
#include <limits.h>

int strcasecmp(char* str1, char* str2) {
    int i = 0, diff, flag = 0;
    char a, b;
    while(str1[i] != '\0' && str2[i] != '\0') {
        a = str1[i];
        b = str2[i];
        
        if((a >= 65 && a <= 90) && (b >= 97 && b <= 122))
            diff = a - b + 32;
        else if((a >= 97 && a <= 122) && (b >= 65 && b <= 90))
            diff = a - b - 32;
        else
            diff = a - b;
        
        if(diff > 0)
            return INT_MAX;
        else if(diff < 0)
            return INT_MIN;

        i++;
    }

    if(str1[i] == '\0' && str2[i] == '\0')
        return 0;
    else if(str1[i] == '\0')
        return INT_MIN;
    else
        return INT_MAX;
}

char* strsep(char** stringp, char* delim) {
    if (*stringp == NULL) {
        return NULL;
    }

    char* start = *stringp;
    char* p = start;

    while (*p != '\0') {
        const char* d = delim;
        while (*d != '\0') {
            if (*p == *d) {
                *p = '\0';
                *stringp = p + 1;
                return start;
            }
            d++;
        }
        p++;
    }

    *stringp = NULL;
    return start;
}

int strcoll(char* str1, char* str2) {
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0') {
        if(str1[i] - str2[i] > 0)
            return 1;
        else if(str1[i] - str2[i] < 0)
            return -1;
        i++;
    }

    if(str1[i] == '\0' && str2[i] == '\0')
        return 0;
    else if(str1[i] == '\0')
        return -1;
    else
        return 1;
}

int main() {
    char s1[] = "Data", s2[] = "data", s3[] = "Structures", s4[] = "struct", s5[] = "data structures and algorithms";
    char *p = s5, *token;
    
    printf("Comparison of strings using strcasecmp: %d\n", strcasecmp(s1, s2));
    printf("Tokenizing a string using strsep:\n");
    while ((token = strsep(&p, " ")) != NULL) {
        printf("%s\n", token);
    }
    printf("Comparison of strings using strcoll: %d", strcoll(s3, s4));

    return 0;
}