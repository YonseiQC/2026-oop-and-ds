#include <iostream>
#include <vector>

void func(int a) {
	std::cout << "Function for int\n";
}
void func(double b) {
	std::cout << "Function for double\n";
}
void func(const std::string& str) {
	std::cout << "Function for string\n";
}
void func(const std::vector<double>& vec) {
	std::cout << "Function for vector<double>\n";
}

int main() {
	func(1); // print "Function for int"
	func(1.0); // print "Function for double"
	func("str"); // print "Function for string"
	func(std::vector<double>{1.0, 2.0}); // print "Function for vector<double>"
	return 0;
}
