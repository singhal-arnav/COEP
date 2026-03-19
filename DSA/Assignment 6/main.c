#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"

#define MAX_HEAP_SIZE 100
#define MAX_DIGITS 10

int main(int argc, char **argv){
	heap h1;
	int fd, i = 0, flag;
	char buffer[MAX_DIGITS];

	init_heap(&h1, MAX_HEAP_SIZE);

	if((fd = open(argv[1], O_RDONLY)) == -1) {
		perror("Error - File could not be opened\n");
		return 1;
	}
	
	while(read(fd, &buffer[i], 1)) {
		if(buffer[i] >= 48 && buffer[i] <= 57) {
			flag = 0;
			i++;
			continue;
		}
		if(!flag && strchr(", \t\n", buffer[i])) {
			buffer[i] = '\0';
			i = 0;
			insert_heap(&h1, atoi(buffer));
			flag = 1;
			continue;
		}
	}

	if (i > 0 && !flag) {
		buffer[i] = '\0';
		insert_heap(&h1, atoi(buffer));
	}
	
	close(fd);
	
	printf("Contents of heap: ");
	print_heap(h1);
	printf("Sorted in ascending order: ");
	heap_sort(&h1);

	return 0;
}
