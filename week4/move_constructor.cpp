#include <vector>
#include <numeric>
#include <iostream>

int main() {
	std::vector<int> a(100,0);
	std::iota(std::begin(a), std::end(a), 0);

	std::vector<int> b = std::move(a);
	std::cout << a.size() << '\n'; // prints 0
	return 0;
}
