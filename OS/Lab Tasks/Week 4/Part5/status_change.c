#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int pid = getpid();
    char cmd[100];
    snprintf(cmd, sizeof(cmd), "grep State /proc/%d/status", pid);
    printf("Proc States:\n");
    //Runnable
    for(int i = 0; i < 500000000; ++i) { // temp loop to show sleeping states
        if(i % 100000000 == 0) {
            system(cmd);
        }
    }
    //Sleeping
    system(cmd);
    sleep(5);
    system(cmd);

    //entry for child becoming zombie
    int pid_2 = fork();
    if (pid_2 == 0) {
        printf("Child PID: %d, this will become zombie after parent reaps\n", getpid());
        exit(0);
    } 
    else {
        char child_cmd[100];
        snprintf(child_cmd, sizeof(child_cmd), "grep State /proc/%d/status", pid_2);
        printf("Checking child state for 5 secs\n");
        for (int i = 0; i < 5; i++) {
            system(child_cmd);
            sleep(1);
        }
        wait(NULL);
    }
}
