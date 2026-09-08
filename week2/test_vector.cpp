#include <iostream>
#include <vector>
int main() {
	std::vector<int> arr{1,2,3,4};
	for(int i = 0; i < 100; i++) {
		arr.push_back(i);
	}
	for(int val: arr) {
		std::cout << val << ", ";
	}
	return 0;
} 
