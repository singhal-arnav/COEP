#include <stdio.h>

int gcd(int num1, int num2) {
    if(num1 > num2) {
        if(num1 % num2 == 0)
            return num2;
        else
            return gcd(num1 % num2, num2);
    }
    else {
        if(num2 % num1 == 0)
            return num1;
        else
            return gcd(num1, num2 % num1);
    }
}

int main() {
    int n1, n2;
    printf("Enter the first number: ");
    scanf("%d", &n1);
    printf("Enter the second number: ");
    scanf("%d", &n2);

    printf("GCD of the numbers = %d", gcd(n1, n2));
    return 0;
}