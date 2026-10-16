#include <string>
#include <iostream>
#include "string_sum.hpp"
#include "spider_man.hpp"

int main() {
	std::string c = sum("Hello, ", "world!");
	std::string d = spider_man();
	std::cout << c << '\n' << d << '\n';
	return 0;
}
