#include <iostream>
#include <format>

int main() {
	auto sum = [](int a, int b) -> int {
		return a+b;
	};
	std::cout << sum(5, 4) << '\n'; // prints 9

	const int c = 30;
	auto add_c = [=](int s) -> int {
		return c + s;
	};

	std::cout << add_c(5) << '\n'; // prints 35

	int d = 30;
	auto add_to_d = [&](int s) {
		d += s;
	};
	add_to_d(20);
	std::cout << d << '\n'; // prints 50

	int e = 30;
	auto add_to_e = [=](int s) {
		e += s; // compile error!
	};

	int e = 30;
	auto add_to_e = [=](int s) mutable {
		e += s;
	};
	add_to_e(15);
	std::cout << e << '\n'; // prints 30
	return 0;
}
