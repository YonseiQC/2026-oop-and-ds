#include <vector>
#include <string>
#include <format>
#include <iostream>

// Do not take too much attention to this function now
std::string format_vector(const std::vector<int>& vec) {
	std::string res = "[";
	if (vec.size() == 0) {
		res += "]";
		return res;
	}

	for(int i = 0; i < vec.size()-1; i++) {
		res += std::format("{},", vec[i]);
	}
	res += std::format("{}]", vec.back());
	return res;
}

int main() {
	std::vector<int> v;
	for(int i = 0; i < 10; i++) {
		v.push_back(i);
	}

	auto it = std::begin(v);
	// we can change the value it refers to
	*it = 10;
	std::cout << format_vector(v) << '\n';

	auto cit = std::cbegin(v);
	// the following line does not compile
	// *cit = 10; 
	// still we can
	++cit;

	const auto it2 = std::begin(v);
	// and the following line does not compile 
	// ++it2;
	
	// and reverse iterator
	for(auto rit = std::rbegin(v); rit != std::rend(v); ++rit) {
		std::cout << *rit << ", ";
	}
	std::cout << '\n';
	return 0;
}
