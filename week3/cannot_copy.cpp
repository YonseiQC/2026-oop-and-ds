#include <iostream>
void func(std::basic_ostream<char>& stream) {
	stream << "Does it work?\n";
}
int main() {
	func(std::cout);
	return 0;
}
