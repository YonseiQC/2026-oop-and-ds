#include <iostream>

constexpr int fib(int n) {
	if (n <= 1) {
		return n;
	}
	return fib(n-1) + fib(n-2);
}

int main() {
	constexpr int ret = fib(30);
	return ret;
}
