#include <algorithm>
#include <vector>
#include <format>
#include <string>
#include <iostream>

// Do not take too much attention to this function now
std::string format_vector(const std::vector<int>& vec) {
	std::string res = "[";
	if (vec.size() == 0) {
		res += "]";
		return res;
	}

	for(int i = 0; i < vec.size()-1; i++) {
		res += std::format("{},", vec[i]);
	}
	res += std::format("{}]", vec.back());
	return res;
}

bool descending(int a, int b) {
	return a > b;
}

int main() {
	std::vector<int> arr = {5, 3, 1, 0, 8, 9, 10};

	std::sort(std::begin(arr), std::end(arr)); // ascending order
	std::cout << format_vector(arr) << '\n';

	std::sort(std::begin(arr), std::end(arr), descending); // descending order
	std::cout << format_vector(arr) << '\n'; 

	return 0;
}
