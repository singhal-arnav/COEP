#include <stdio.h>
#include <unistd.h>

int main() {
    printf("PID of original process: %d\n", getpid());

    int pid1 = fork();

    if(pid1 == 0) {
        printf("PID of Child A: %d\n", getpid());
        int pid11 = fork();
        if(pid11 == 0) {
            printf("PID of Child A1: %d\n", getpid());
        }
    } 
    else {
        int pid2 = fork();
        if(pid2 == 0) {
            printf("PID of Child B: %d\n", getpid());
        }
    }

    return 0;
}

