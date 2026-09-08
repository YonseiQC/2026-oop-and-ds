#include <iostream>
int main() {
	int arr[5] = {1, 2, 3, 4, 5};
	const int* pt1 = &arr[1];
	int* const pt2 = &arr[1];
	const int * const pt = &arr[2];

	// pointer const
	*pt2 = 4;
	++pt2;
	std::cout << arr[1] << '\n';

	return 0;
}
