#include <stdio.h>

int main() {
    int units;
    float cost, surcharge;

    printf("Enter number of units consumed: ");
    scanf("%d", &units);

    if(units <= 50)
        cost = units * 0.5;
    else if(units <= 150)
        cost = 50 * 0.5 + (units - 50) * 0.75;
    else if(units <= 250)
        cost = 50 * 0.5 + 100 * 0.75 + (units - 150) * 1.2;
    else
        cost = 50 * 0.5 + 100 * 0.75 + 150 * 1.2 + (units - 250) * 1.5;
    
    surcharge = 0.2 * cost;

    printf("Total electricity bill = Rs. %.2f", cost + surcharge);

    return 0;
}