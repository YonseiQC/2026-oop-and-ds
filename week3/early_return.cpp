#include <iostream>

void my_sort(int* arr, int length) {
	if(length < 1) {
		return ;
	}
	bool sorted = true;
	for(int i = 0; i < length-1; i++) {
		if(arr[i] >= arr[i+1]) {
			sorted = false;
			break;
		}
	}
	if(sorted) {
		return ;
	}

	for(int i = 0; i < length-1; i++) {
		for(int j = i; j < length; j++) {
			if(arr[i] > arr[j]) {
				int val = arr[i];
				arr[i] = arr[j];
				arr[j] = val;
			}
		}
	}
}

int main() {
	int arr[10] = {3, 8, 1, 2, 5, 3, 6, 13, 0, 19};
	my_sort(arr, 10);

	for(int i = 0; i < 10; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << '\n';
	return 0;
}
