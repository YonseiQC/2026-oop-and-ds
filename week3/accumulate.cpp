#include <iostream>
#include <vector>
#include <numeric>
#include <format>

int main() {
	std::vector<int> vec(10); // vector of 10 elements
							  // This is different from vec{10}
							  // which makes a vector contains
							  // single element
	std::iota(std::begin(vec), std::end(vec), 1);
	// vec = [1,2,3,4,5,6,7,8,9,10]

	auto sum = std::accumulate(std::begin(vec), std::end(vec), 0); // == 55
	auto mul = std::accumulate(std::begin(vec), std::end(vec), 1, [](int a, int b) {
		return a*b;
	});

	std::vector<std::string> str_vec{"ghi", "abc", "def"};
	auto str = std::accumulate(std::begin(str_vec), std::end(str_vec), std::string(""));
	std::cout << str << '\n';

	std::cout << std::format("Sum is {}\n", sum);
	std::cout << std::format("mul is {}\n", mul);

	return 0;
}
