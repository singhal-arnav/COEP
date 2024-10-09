#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c, d, x1, x2;
    printf("Enter the coefficient of x^2: ");
    scanf("%f", &a);
    printf("Enter the coefficient of x: ");
    scanf("%f", &b);
    printf("Enter the constant term: ");
    scanf("%f", &c);

    d = b * b - (4 * a * c);

    if(d >= 0) {
        printf("x = %f, %f", ((-b + sqrt(d))/ (2 * a)), ((-b - sqrt(d))/ (2 * a)));
    }
    else{
        printf("Roots are imaginary as discriminant is negative\n");
        x1 = -b / (2 * a);
        x2 = sqrt(-d) / (2 * a);
        printf("x = %f + %fi, %f - %fi", x1, x2, x1, x2);
    }

    return 0;
}