#include <stdio.h>

int lcm(int num1, int num2) {
    //LCM = Product of the numbers / GCD; Here the GCD is calculated first, and then the LCM is computed from it
    int gcd, prod = num1 * num2;
    while(1) {
        if(num1 > num2) {
            if(num1 % num2 == 0) {
                gcd = num2;
                break;
            }
            else
                num1 = num1 % num2;
        }
        else {
            if(num2 % num1 == 0) {
                gcd = num1;
                break;
            }
            else
                num2 = num2 % num1;
        }
    }

    return prod/gcd;
}

int main() {
    int n1, n2;
    printf("Enter the first number: ");
    scanf("%d", &n1);
    printf("Enter the second number: ");
    scanf("%d", &n2);

    printf("LCM of the numbers = %d", lcm(n1, n2));
    return 0;
}