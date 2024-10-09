#include <stdio.h>

int main() {
    int basic_sal, hra, da;

    printf("Enter the basic salary of the employee: ");
    scanf("%d", &basic_sal);

    if(basic_sal <= 10000) {
        hra = 20 * basic_sal / 100;
        da = 80 * basic_sal / 100;
    }
    else if(basic_sal <= 20000) {
        hra = 25 * basic_sal / 100;
        da = 90 * basic_sal / 100;
    }
    else {
        hra = 30 * basic_sal / 100;
        da = 95 * basic_sal / 100;
    }

    printf("Gross salary = %d", (basic_sal + hra + da));
    return 0;
}