#include <iostream>
class TestClass {
private:
	int& a_;
public:
	TestClass(int& a) : a_{a} {
	}

	void set_a(int val) {
		a_ = val;
	}
};

int main() {
	int c = 0;
	TestClass test(c);

	test.set_a(30);
	std::cout << c << '\n';
	return 0;
}
