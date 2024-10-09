#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846
#define TERMS 10 // Number of terms in Taylor series

double factorial(int n) {
    double result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

double sine(double x) {
    double result = 0;
    for (int i = 0; i < TERMS; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;
        result += sign * pow(x, 2 * i + 1) / factorial(2 * i + 1);
    }
    return result;
}

double cosine(double x) {
    double result = 0;
    for (int i = 0; i < TERMS; i++) {
        int sign = (i % 2 == 0) ? 1 : -1;
        result += sign * pow(x, 2 * i) / factorial(2 * i);
    }
    return result;
}

double sine_inverse(double x) {
    double guess = x;
    for (int i = 0; i < TERMS; i++) {
        guess -= (sine(guess) - x) / cosine(guess); // Newton's method
    }
    return guess;
}

double cosine_inverse(double x) {
    return (PI / 2) - sine_inverse(x);
}

double tan(double x) {
    return sine(x) / cosine(x);
}

int main() {
    double x;

    printf("Enter a value in radians: ");
    scanf("%lf", &x);

    printf("Sine of %lf = %lf\n", x, sine(x));
    printf("Cosine of %lf = %lf\n", x, cosine(x));
    printf("Tangent of %lf = %lf\n", x, tan(x));

    printf("Enter the value of sine of some angle: ");
    scanf("%lf", &x);
    printf("Checking if sine(sine_inverse(%lf)) returns %lf\n", x, x);
    printf("sine(sine_inverse(%lf)) = %lf\n", x, sine(sine_inverse(x)));

    printf("Enter the value of cosine of some angle: ");
    scanf("%lf", &x);
    printf("Checking if cosine(cosine_inverse(%lf)) returns %lf\n", x, x);
    printf("cosine(cosine_inverse(%lf)) = %lf\n", x, cosine(cosine_inverse(x)));

    return 0;
}