#include <fstream>
#include <map>
#include <iostream>
#include <vector>
#include <string>

constexpr unsigned int SHIFT = 7;

unsigned int hash(const std::string& word) {
	unsigned int h = 0;
	for(const char c: word) {
		h = (h << SHIFT) | (h >> (32 - SHIFT));
		h += (unsigned int)c;
	}
	return h;
}

struct Entry {
	std::string name;
	unsigned int midterm_score;
};

template <>
class std::hash<Entry> {
public:
	size_t operator()(const Entry& entry) {
		std::hash<std::string> string_hasher;
		std::hash<unsigned int> uint_hasher;
		return (string_hasher(entry.name) * 51) | uint_hasher(entry.midterm_score);
	}
};

int main() {
	std::ifstream fin("google-10000-english.txt");

	std::map<unsigned int, std::vector<std::string>> counts;

	std::hash<std::string> std_hash; // function object
	
	while(!fin.eof()) {
		std::string word;
		fin >> word;
		counts[std_hash(word)].push_back(word);
	}

	int max = 0;
	unsigned int max_key;
	for(const auto [k, v]: counts) {
		if (max < v.size()) {
			max = v.size();
			max_key = k;
		}
	}
	std::cout << "The maximum number of collision: " << max << '\n';
	for(const auto word: counts[max_key]) {
		std::cout << word << '\t' << hash(word) << '\n';
	}
	return 0;
}
