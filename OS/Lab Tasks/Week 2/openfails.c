#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main() {
	printf("Attempting to open file which does not exist\n");
	printf("Value returned by open(): %d\n", open("abc.txt", O_RDONLY));
	printf("Error code: %d\n\n", errno);
	
	printf("Attempting to open file to which access is forbidden\n");
	printf("Value returned by open(): %d\n", open("/root", O_RDONLY));
	printf("Error code: %d\n\n", errno);
	
	printf("Attempting to create new file with same name as existing file using O_EXCL flag\n");
	printf("Value returned by open(): %d\n", open("testing.txt", O_WRONLY | O_CREAT | O_EXCL));
	printf("Error code: %d\n", errno);

	return 0;
}
