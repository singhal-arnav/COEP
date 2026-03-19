#include <stdio.h>

int f(int n) {
	if(n == 0 || n == 1)
		return 1;
	return n * f(n - 1);
}

int main() {
	printf("Factorial of 9: %d\n", f(9));
	
	return 0;
}
