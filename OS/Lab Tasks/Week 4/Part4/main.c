#include <stdio.h>
#include <unistd.h>

int main() {
	int n;
	
	printf("PID of the current process: %d\n", getpid());
	
	scanf("%d", &n);

	return 0;
}
