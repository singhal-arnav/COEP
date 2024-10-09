#include <stdio.h>
#include <stdlib.h>

char* bin(int num) {
    if(num == 0)
        return "0";
    char* p = (char*)malloc(50 * sizeof(char));
    int i = 0, temp;
    while(num) {
        p[i+1] = p[i];
        p[i] = (num % 2)? '1':'0';
        num /= 2;
        i++;
    }

    //Reversing the string
    for(int j = 0; j < i/2; j++) {
        temp = p[j];
        p[j] = p[i - j - 1];
        p[i - j - 1] = temp;
    }
    
    p[i] = '\0';
    return p;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    char* p = bin(num);
    printf("Binary representation: %s", p);
    return 0;
}