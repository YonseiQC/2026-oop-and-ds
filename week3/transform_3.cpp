#include <algorithm>
#include <iostream>
#include <deque>

int mul2_add1(int val) {
	return 2*val + 1;
}

void print(int val) {
	std::cout << val << '\n';
}

int main() {
	std::deque<int> vec = {1, 2, 3, 4, 5};
	std::deque<int> res;
	std::transform(std::begin(vec), std::end(vec), std::front_inserter(res), mul2_add1);

	std::for_each(std::begin(res), std::end(res), print);
	return 0;
}
