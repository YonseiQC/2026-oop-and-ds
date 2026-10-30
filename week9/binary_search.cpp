#include <iostream>
#include <vector>

// Find an element from a given sorted array
// If there is such an element, return the index
// Otherwise, return -1
int binary_search(const int* a, int begin,
		int end, int target) {
	if (begin >= end) { return -1; }

	int mid = begin + (end - begin) / 2;

	if (a[mid] == target) { return mid; }

	if (target < a[mid]) {
		return binary_search(a, begin, mid, target);
	}

	return binary_search(a, mid + 1, end, target);
}

int main() {
	std::vector<int> arr{1, 2, 8, 9, 100, 123, 1000};
	std::cout << binary_search(arr.data(), 0, arr.size(), 20) << '\n'; // Prints -1 since 20 is not in the vector
	std::cout << binary_search(arr.data(), 0, arr.size(), 123) << '\n'; // Prints 5 since arr[5]==123
	return 0;
}
