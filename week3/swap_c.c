void swap(int& a, int& b) {
	int c;
	c = a;
	a = b;
	b = c;
}
int main() {
	int a = 10;
	int b = 4;
	swap(a, b);
	return 0;
}
