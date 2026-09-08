#include <format>
#include <iostream>

int main() {
	std::cout << std::format("{}, {}!\n", "Hello", "World");
	std::cout << std::format("{} is one\n", 1);
	std::cout << std::format("{:d} is one\n", 1); // Can be more specific
	std::cout << std::format("{:f} is one point zero\n", 1.0);
	std::cout << std::format("{:.3f} is one point zero\n", 1.0);

	std::cout << std::format("{:04d} is one\n", 1); 
	
	// The following line raises compile error!
	std::cout << std::format("{:d} is one\n", 1.23);

	return 0;
}
