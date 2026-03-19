#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        execl("/bin/echo", "echo", "execl success", NULL);
        perror("execl failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        char *args[] = {"echo", "execvp success", NULL};
        execvp("echo", args);
        perror("execvp failed");
        exit(1);
    }
    wait(NULL);

    pid = fork();
    if (pid == 0) {
        execlp("echo", "echo", "execlp success", NULL);
        perror("execlp failed");
        exit(1);
    }
    wait(NULL);

    return 0;
}

