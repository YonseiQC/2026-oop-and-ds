#include <algorithm>
#include <iostream>
#include <vector>

void insertion_sort(int* arr, int length) {
	// [0,1) is sorted
	for(int i = 1; i < length; i++) {
		// [0,i) is sorted
		int j = i;
		while(j > 0 && arr[j-1] > arr[j]) {
			// [0,j) and [j,i] are sorted
			std::swap(arr[j-1], arr[j]);
			// [0,j-1) and [j-1,i] are sorted
			--j;
			// [0,j) and [j,i] are sorted
		}
		// [0:j) and [j,i] are sorted
		// and arr[j-1] <= arr[j]
		// which implies that [0,i]=[0,i+1) is sorted
	}
	// At termination, [0,length) is sorted
}

int main() {
	std::vector<int> arr{1, -3, 4, -8, 4};
	insertion_sort(arr.data(), arr.size());

	for(int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << '\t';
	}
	std::cout << '\n';
	return 0;
}
