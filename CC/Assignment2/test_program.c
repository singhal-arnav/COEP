#include <stdio.h>

int main()
{
    int a = 10;
    int b = 20;
    float c = 3.14;
    char d = 'A';
    char *s = "Hello";
    int arr[5];
    int *p = &a;

    a += 1;
    a -= 1;
    a *= 2;
    a /= 2;
    a %= 3;
    a++;
    a--;

    if (a == b) {
        a = 1;
    } else if (a != b && a < b) {
        a = 2;
    } else if (a <= b || a > b) {
        a = 3;
    }

    a = b >= 10 ? 1 : 0;

    int mask = a & b;
    int bits = a | b;
    int flip = a ^ b;
    int notb = ~b;
    int left = a << 2;
    int right = b >> 2;

    arr[0] = a;
    *p = 5;

    // single line comment
    /* multi
       line
       comment */

    return 0;
}
