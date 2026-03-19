#include <stdio.h>

int main() {
    int month_num;
    printf("Enter the month number: ");
    scanf("%d", &month_num);
    if(month_num <= 7) {
        if(month_num == 2)
            printf("%d", 28);
        else if(month_num % 2)
            printf("%d", 31);
        else
            printf("%d", 30);
    }
    else {
        if(month_num % 2 == 0)
            printf("%d", 31);
        else
            printf("%d", 30);
    }
    return 0;
}