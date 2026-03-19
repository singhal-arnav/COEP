#include "thread.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

void *worker1(void *arg) {
    const char *name = (const char *)arg;
    for (int i = 0; i < 3; ++i) {
        printf("[%s] pid = %d, tid = %ld, iteration = %d\n", name, getpid(), syscall(SYS_gettid), i);
        sleep(1);
    }
    return "multithreading";
}

void *worker2(void *arg) {
    const char *name = (const char *)arg;
    printf("[%s] pid = %d, tid = %ld running and will call thread_exit()\n", name, getpid(), syscall(SYS_gettid));
    thread_exit((void *)42);
}

int main(void) {
    printf("main(): pid = %d, tid = %ld\n", getpid(), syscall(SYS_gettid));

    int t1, t2, t3;
    if (thread_create(&t1, worker1, "Thread 1") != 0) {
        perror("Failed to create thread t1\n");
        return 1;
    }
    if (thread_create(&t2, worker1, "Thread 2") != 0) {
        perror("Failed to create thread t2\n");
        return 1;
    }
    if (thread_create(&t3, worker2, "Thread 3") != 0) {
        perror("Failed to create thread t3\n");
        return 1;
    }

    void *r1 = NULL, *r2 = NULL, *r3 = NULL;

    if (thread_join(t1, &r1) != 0) {
        perror("Failed to join thread t1\n");
		return 1;
	}
    else
        printf("Joined t1 (tid = %d), return value (string) = %s\n", t1, (char *)r1);

    if (thread_join(t2, &r2) != 0) {
        perror("Failed to join thread t2\n");
		return 1;
	}
    else
        printf("Joined t2 (tid = %d), return value (string) = %s\n", t2, (char *)r2);

    if (thread_join(t3, &r3) != 0) {
        perror("Failed to join thread t3\n");
		return 1;
	}
    else
        printf("Joined t3 (tid = %d), return value (long) = %ld\n", t3, (long)r3);
    
    // Calling thread_join() again on t3 to check if it fails
    if (thread_join(t3, &r3) != 0) {
        perror("Failed to join thread t3");
		return 1;
	}
    else
        printf("Joined t3 (tid = %d), return value (long) = %ld\n", t3, (long)r3);

    printf("main() exiting\n");
    return 0;
}

