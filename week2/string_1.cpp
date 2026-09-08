#include <iostream>
#include <cstdio> // This is how to include C header into C++
#include <cstring>

int main() {
    const char* correct_answer = "Donald Trump";

	std::cout << "Who is the current US president (without middle name)?\n";
	while(true) {
		char str[255]; // Please get used to declare variable close to where it is used
		std::cin.getline(str, 255);

		// The following line is always false!
		if (str == correct_answer) {
			std::cout << "Correct answer!\n";
			break;
		}
		std::cout << "Wrong. Try again!\n";
	}
    return 0;
}
