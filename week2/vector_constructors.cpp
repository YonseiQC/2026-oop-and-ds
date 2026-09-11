#include <vector>
#include <string>

int main() {
	// initialization list
	std::vector<int> v1{1,2,3,4,5};
	// vector filled with 100 strings
	std::vector<std::string> v2(100, "Hello, world!");
	// using iterators
	std::string str = "Hello, world!";
	std::vector<char> v3(std::begin(str), std::end(str));
	return 0;
}
