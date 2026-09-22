#include <algorithm>
#include <vector>
#include <format>
#include <string>
#include <iostream>

class Func {
private:
	int c_;
public:
	Func(int c) : c_{c} {
	}

	bool operator()(int a, int b) {
		if (a > c_ && b > c_) {
			return a > b;
		} else {
			return a < b;
		}
	}
};

int main() {
	std::vector<int> arr = {5, 3, 1, 0, 8, 9, 10};

	Func func(3);
	bool res = func(3, 5);

	int c = 4;
	/*
	Func(c) is the same as the following lambda function
	[=](int a, int b) -> bool {
		if (a > c && b > c) {
			return a > b;
		} else {
			return a < b;
		}
	}
	*/
	std::sort(std::begin(arr), std::end(arr), Func(c));
	return 0;
}
