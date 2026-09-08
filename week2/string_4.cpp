#include <string>
#include <iostream>

int main() {
	const std::string str = "This is string";

	for(int i = 0; i < str.size(); i++) {
		std::cout << str[i] << "\n";
	}

	for(int i = 0; i < str.size(); i++) {
		std::cout << str.at(i) << "\n";
	}

	// std::cout << str[20]; // Wrong, but no error
	std::cout << str.at(20); // Wrong and raise an exception
	return 0;
}
