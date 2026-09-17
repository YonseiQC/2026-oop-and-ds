#include <vector>
#include <string>
#include <iostream>

int main() {
	// initialization list
	std::vector<int> v1{1,2,3,4,5};
	// vector filled with 100 strings
	std::vector<std::string> v2(100, "Hello, world!");
	// using iterators
	std::string str = "Hello, world!";
	std::vector<char> v3(std::begin(str), std::end(str));

	int a[5] = {0,1,2,3,4};
	std::vector<int> v4(&a[0], &a[5]);
	return 0;
}
