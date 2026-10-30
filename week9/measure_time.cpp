#include <iostream>
#include <chrono>
#include <random>
#include <format>
#include <limits>
#include <algorithm>

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << std::format("Usage: {} [size_of_array]\n", argv[0]);
		return 1;
	}

	int size = stoi(std::string(argv[1]));

	std::vector<int> arr;
	std::mt19937 re{1557};
	std::uniform_int_distribution<int> dist(
			std::numeric_limits<int>::min(),
			std::numeric_limits<int>::max());
	for(int i = 0; i < size; i++) {
		arr.push_back(dist(re));
	}

	auto start = std::chrono::system_clock::now();
	std::sort(std::begin(arr), std::end(arr));
	auto end = std::chrono::system_clock::now();
	auto runtime = 
		std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << std::format("Runtime: {}\n", runtime);
	return 0;
}
