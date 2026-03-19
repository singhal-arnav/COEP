int g(int n) {
	if(n == 0 || n == 1)
		return 1;
	else
		return n * g(n - 1);
}
