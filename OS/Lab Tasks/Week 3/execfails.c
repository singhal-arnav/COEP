#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
	
	execl("/nonexistent/path/test", "test", "random", NULL); // fails as the executable does not exist (invalid path)
	printf("Error code: %d\n", errno); // prints error code
	printf("%s\n", strerror(errno)); // prints error message
	
	execl("execfails.c", "execfails", NULL); // fails as file exists but it is not executable
	printf("Error code: %d\n", errno);
	printf("%s\n", strerror(errno));
	
	return 0;
}
