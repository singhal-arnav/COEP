#include "polynomial.c"

int main() {
    poly p1, p2, sum, diff;
    int n1, n2, i, coeff, exp;

    printf("Enter number of terms to be stored in the first polynomial: ");
    scanf("%d", &n1);
    printf("Enter number of terms to be stored in the second polynomial: ");
    scanf("%d", &n2);

    init_poly(&p1, n1);
    init_poly(&p2, n2);

    printf("Enter the coefficient and exponent of each term of the first polynomial:\n");
    for(i = 1; i <= p1.n; i++) {
        printf("Coefficient of term %d: ", i);
        scanf("%d", &coeff);
        printf("Exponent of term %d: ", i);
        scanf("%d", &exp);
        append(&p1, coeff, exp);
    }

    printf("Enter the coefficient and exponent of each term of the second polynomial:\n");
    for(i = 1; i <= p2.n; i++) {
        printf("Coefficient of term %d: ", i);
        scanf("%d", &coeff);
        printf("Exponent of term %d: ", i);
        scanf("%d", &exp);
        append(&p2, coeff, exp);
    }

    printf("Polynomial 1: ");
    display(p1);
    printf("Polynomial 2: ");
    display(p2);

    init_poly(&sum, (n1 > n2) ? n1 : n2);
    add_poly(&p1, &p2, &sum);
    printf("Sum of the polynomials: ");
    display(sum);

    init_poly(&diff, (n1 > n2) ? n1 : n2);
    sub_poly(&p1, &p2, &diff);
    printf("Difference of the polynomials: ");
    display(diff);

    return 0;
}