#include "stdio.h"

int main()
{
    int i = 1, j;
    for ( ; ; )
    {
        if (i)
            j = --i;
        if (j < 10)
            printf("HelloWorld", j++);
        else
            break;
    }
    return 0;
}