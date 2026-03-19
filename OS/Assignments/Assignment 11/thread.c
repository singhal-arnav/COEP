#define _GNU_SOURCE
#include "thread.h"
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdatomic.h>
#include <sys/syscall.h>

#define THREAD_STACK_SIZE (1024 * 1024)

typedef struct thread_node {
    int tid;
    void *stack;
    void *retval;
    int exited;
    struct thread_node *next;
} thread_node;

static thread_node *thread_list = NULL;

static atomic_flag list_lock = ATOMIC_FLAG_INIT;

static void lock_list() {
    while(atomic_flag_test_and_set_explicit(&list_lock, memory_order_acquire));
}

static void unlock_list() {
    atomic_flag_clear_explicit(&list_lock, memory_order_release);
}

static void list_insert(thread_node *node) {
    lock_list();
    node->next = thread_list;
    thread_list = node;
    unlock_list();
}

static thread_node *list_find(int tid) {
    lock_list();
    thread_node *t = thread_list;
    while(t) {
        if(t->tid == tid)
			break;
        t = t->next;
    }
    unlock_list();
    return t;
}

static thread_node *list_remove(int tid) {
    lock_list();
    thread_node *prev = NULL;
    thread_node *t = thread_list;
    while(t) {
        if(t->tid == tid) {
            if(prev)
				prev->next = t->next;
            else
				thread_list = t->next;
            t->next = NULL;
            unlock_list();
            return t;
        }
        prev = t;
        t = t->next;
    }
    unlock_list();
    return NULL;
}

struct start_info {
    void *(*start_routine)(void *);
    void *arg;
    thread_node *node;
};

static int thread_start_wrapper(void *void_arg) {
    struct start_info *s = (struct start_info *)void_arg;
	struct start_info sinfo = *s;
	free(s);

    void *(*func)(void *) = sinfo.start_routine;
    void *arg = sinfo.arg;
    thread_node *node = sinfo.node;

    void *ret = func(arg);
    node->retval = ret;
    node->exited = 1;

    _exit(0);
}

int thread_create(int *tid, void *(*start_routine)(void *), void *arg) {
    if(!tid || !start_routine) {
        errno = EINVAL;
        return -1;
    }

    void *stack = malloc(THREAD_STACK_SIZE);
    if(!stack) {
        errno = ENOMEM;
        return -1;
    }

    thread_node *node = malloc(sizeof(thread_node));
    if(!node) {
        free(stack);
        errno = ENOMEM;
        return -1;
    }

    node->tid = 0;
    node->stack = stack;
    node->retval = NULL;
    node->exited = 0;
    node->next = NULL;

    struct start_info sinfo;
    sinfo.start_routine = start_routine;
    sinfo.arg = arg;
    sinfo.node = node;

    struct start_info *sinfo_heap = malloc(sizeof(struct start_info));
    if(!sinfo_heap) {
        free(stack);
        free(node);
        errno = ENOMEM;
        return -1;
    }
    *sinfo_heap = sinfo;

    int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD;

    int tid_clone = clone(thread_start_wrapper, (char *)stack + THREAD_STACK_SIZE, flags, sinfo_heap);
    if(tid_clone == -1) {
        free(stack);
        free(node);
        free(sinfo_heap);
        return -1;
    }

    node->tid = tid_clone;
    list_insert(node);

    *tid = tid_clone;
    return 0;
}

int thread_join(int tid, void **retval_out) {
    if(tid <= 0) {
        errno = EINVAL;
        return -1;
    }

    int status;
    int r = waitpid(tid, &status, 0);
    if(r == -1) {
        return -1;
    }

    thread_node *node = list_remove(tid);
    if(!node) {
        if(retval_out)
			*retval_out = NULL;
        return 0;
    }

    if(retval_out)
		*retval_out = node->retval;

    if(node->stack)
		free(node->stack);
    free(node);

    return 0;
}

void thread_exit(void *retval) {
    int self_tid = (int)syscall(SYS_gettid);
    thread_node *node = list_find(self_tid);
    if(node) {
        node->retval = retval;
        node->exited = 1;
    }
    _exit(0);
}

