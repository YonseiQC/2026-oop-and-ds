int main() {
	auto sum = [](int a, int b){
		return a+b;
	};
	int val = sum(10, 30);

	int val2 = [](int a, int b){
		return a+b;
	}(10, 3);
	return 0;
}
