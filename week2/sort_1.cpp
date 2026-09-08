#include <iostream>
#include <format>
#include <string>
#include <algorithm>
#include <vector>

int main() {
	// std::string a = "This is string";
	// std::vector<int> a{5, 4, 3, 2, 1, 6, 1, 2, 3, 4, 45, 12, 3, 5};
	std::vector<int32_t> a{5.0, 4.0, 3.0, 2.0, 1.0, 6.0, 1.0, 2.0, 3.0, 4.0, 45.0, 12.0, 3.0, 5.0};

	std::sort(std::begin(a), std::end(a));

	for(const auto elt: a) { // range based for
		std::cout << elt << '\n';
	}

	return 0;
}
