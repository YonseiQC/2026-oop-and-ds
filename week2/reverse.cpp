#include <string>
#include <iostream>

std::string reverse(std::string str) {
	return std::string(std::rbegin(str), std::rend(str));
}

int main() {
	std::string str = "Odyssey";
	std::cout << reverse(str);
	return 0;
}
