#include <sys/types.h>

int thread_create(int *tid, void *(*start_routine)(void *), void *arg);
int thread_join(int tid, void **retval_out);
void thread_exit(void *retval);

