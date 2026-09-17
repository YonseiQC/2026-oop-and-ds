#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>

int main() {
	std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
	auto it = std::find_if(std::begin(vec), std::end(vec), [](int val) {
		return val > 9;
	});

	if(it == std::end(vec)) {
		std::cout << "No such element!\n";
	} else {
		std::cout << "Element found!\n";
		std::cout << *it << '\n';
	}

	return 0;
}
