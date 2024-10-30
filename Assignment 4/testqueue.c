#include <stdio.h>
#include "queue.c"

int main() {
    queue q;
    data d;

    qinit(&q);
    while(scanf("%s%u", d.name, &(d.age)) != -1)
        if(!qfull(&q))
            enq(&q, d);
    printf("Dequeueing and displaying data:\n");
    while(!qempty(&q)) {
        d = deq(&q);
        printf("%s %u\n", d.name, d.age);
    }
    return 0;
}
