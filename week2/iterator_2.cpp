#include <string>
#include <iostream>

int main() {
	std::string str = "This is string";
	std::string::const_iterator it = std::begin(str);
	//const std::string::iterator it = std::begin(str);
	++it;
	++it;
	++it;
	*it = 't';

	std::cout << str << '\n';

	return 0;
}
