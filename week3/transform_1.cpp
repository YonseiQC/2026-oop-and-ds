#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <deque>

char my_toupper(char c) {
	return (char)std::toupper(c);
}
int main() {
	const std::string str = "this string has all lowercase letters.";
	std::deque<char> str2;
	std::cout << std::string(std::begin(str2), std::end(str2)) << '\n';

	std::transform(std::begin(str), std::end(str), 
			std::front_inserter(str2), my_toupper);

	// The above line is the same as the following for loop
	/*
	for(auto it = std::begin(str); it != std::end(str); ++it) {
		*it = my_toupper(*it);
	}
	*/

	std::cout << str << '\n';
	std::cout << std::string(std::begin(str2), std::end(str2)) << '\n';
	return 0;
}
