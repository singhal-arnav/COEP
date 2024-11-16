#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "heap.h"

#define MAX_HEAP_SIZE 100

int main(int argc, char **argv){
	heap h1;
	int fd, num;

	init_heap(&h1, MAX_HEAP_SIZE);

	if((fd = open(argv[1], O_RDONLY)) != -1) {
		while(read(fd, &num, sizeof(int))) {
			insert_heap(&h1, num);
		}
	}
	
	print_heap(h1);
	heap_sort(&h1);
	print_heap(h1);
	
	return 0;
}