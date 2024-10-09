#include <stdio.h>

typedef struct fraction {
    int numerator;
    int denominator;
}fraction;

int cmp_fraction(fraction f1, fraction f2) {
    int prod1, prod2;
    prod1 = f1.numerator * f2.denominator;
    prod2 = f2.numerator * f1.denominator;

    if(prod1 > prod2)
        return 1;
    else if(prod1 < prod2)
        return -1;
    else
        return 0;
}

int main() {
    fraction f1, f2;

    printf("Enter the first fraction: ");
    scanf("%d/%d", &f1.numerator, &f1.denominator);
    printf("Enter the second fraction: ");
    scanf("%d/%d", &f2.numerator, &f2.denominator);

    int cmp = cmp_fraction(f1, f2);
    
    if(cmp == 1)
        printf("%d/%d is greater than %d/%d", f1.numerator, f1.denominator, f2.numerator, f2.denominator);
    else if(cmp == -1)
        printf("%d/%d is less than %d/%d", f1.numerator, f1.denominator, f2.numerator, f2.denominator);
    else
        printf("The fractions are equal");

    return 0;
}