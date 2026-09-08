#include <string>
#include <iostream>

int main() {
	std::string str = "This is string";
	// const std::string::iterator
	// std::string::const_iterator
	for(auto it = std::cbegin(str); it != std::cend(str); ++it) {
		std::cout << *it << ", ";
	}
	std::cout << '\n';

	char str2[255] = "This is also string";
	for(char* it = str2; *it != '\0'; ++it) {
		std::cout << *it << ", ";
	}
	std::cout << '\n';
	return 0;
}
