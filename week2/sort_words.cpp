#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
 * std::string a = "abc";
 * std::string b = "adef";
 *
 * (a < b) == true
 */

int main() {
	std::vector<std::string> words;

	while(!std::cin.eof()) {
		std::string line;
		std::cin >> line;

		if(line.empty()) {
			break;
		}

		if (line[line.length()-1] == '\n') {
			line.erase(line.length()-1);
		}
		words.push_back(line);
	}

	std::sort(std::begin(words), std::end(words));

	for(auto word: words) {
		std::cout << word << '\n';
	}

	return 0;
}
