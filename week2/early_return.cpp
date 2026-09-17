#include <iostream>
#include <format>
#include <string>

int very_long_function() {

	bool flag = true;
	bool flag2 = true;
	if(...) {
		return ;
	}
	if(...) {
		return ;
	}
	
}

int main(int argc, char* argv[]) {
	if(argc == 1) {
		std::cout << "This program should take at least one argument.\n";
		return 1;
	}
	for(int i = 0; i < argc; i++) {
		std::cout << std::format("{}-th argument is {}\n", i, argv[i]);
	}
	return 0;
}
