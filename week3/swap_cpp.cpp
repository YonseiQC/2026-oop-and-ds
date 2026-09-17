void swap(int& a, int& b) {
	int c;
	c = a;
	a = b;
	b = c;
}
int main() {
	int val1 = 10;
	int val2 = 4;
	swap(val1, val2);
	return 0;
}
