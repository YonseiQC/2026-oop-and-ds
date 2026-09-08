#include <iostream>
#include <string>

void print_arr(auto arr) {
	for(auto c: arr) {
		std::cout << c << '\n';
	}
}

int main() {
	std::string arr1 = "Donald Trump";
	int arr2[5] = {1, 2, 3, 4 ,5};
	print_arr(arr1);
	print_arr(arr2);
	return 0;
}
