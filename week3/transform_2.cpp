#include <algorithm>
#include <iostream>
#include <string>

char my_toupper(char c) {
	return (char)std::toupper(c);
}
int main() {
	std::string str = "this string has all lowercase letters.";
	std::string str2(str.size(), 'c'); // This string is filled with 'c'
	std::string str3;

	std::cout << str2 << '\n';
	std::transform(std::begin(str), std::end(str), std::begin(str2), my_toupper);
	std::cout << str2 << '\n';

	// or use std::back_inserter
	
	std::cout << str3 << '\n'; 
	std::transform(std::begin(str), std::end(str), std::back_inserter(str3), my_toupper);
	std::cout << str3 << '\n';
	return 0;
}
