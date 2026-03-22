#include <stdio.h>

int first_non_rep_char(char *str) {
    int freqs[26];
    for(int i = 0; i < 26; i++)
        freqs[i] = 0;
    
    int i = 0;
    while(str[i] != '\0') {
        if(str[i] >= 'A' && str[i] <= 'Z')
            freqs[str[i] - 'A']++;
        else
            freqs[str[i] - 'a']++;
        i++;
    }
    
    int j = 0, k;
    while(str[j] != '\0') {
        if(str[j] >= 'A' && str[j] <= 'Z')
            k = str[j] - 'A';
        else
            k = str[j] - 'a';
        if(freqs[k] == 1)
            return j;
        j++;
    }
    
    return -1;
}

int main() {
    char str[100000];
    printf("Enter a string: ");
    scanf("%s", str);
    
    printf("%d\n", first_non_rep_char(str));
    
    return 0;
}
