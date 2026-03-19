#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 100

int mygetchar() {
	char buff[1];
	if(read(0, buff, 1))
		return (int)buff[0];
	else
		return EOF;
}

int myputchar(char s) {
	if(write(1, &s, 1))
		return (int)s;
	else
		return EOF;
}

int main() {
	char ch = mygetchar();
	myputchar(ch);
	printf("\n");
		
	return 0;
}
