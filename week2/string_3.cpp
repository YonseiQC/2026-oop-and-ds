#include <iostream>
#include <cstdio> // This is how to include C header into C++
#include <cstring>

int main() {
    const std::string correct_answer = "Donald Trump";

	std::cout << "Who is the current US president (without middle name)?\n";
	while(true) {
		std::string str;
		std::getline(std::cin, str); // str is called by reference

		if (str == correct_answer) {
			std::cout << "Correct answer!\n";
			break;
		}
		std::cout << "Wrong. Try again!\n";
	}
    return 0;
}
