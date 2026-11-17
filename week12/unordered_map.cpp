#include <unordered_map>
#include <string>
#include <iostream>

int main() {
	std::unordered_map<std::string, int> prices;
	prices["book"] = 3'000;
	prices["car"] = 300'000'000;
	prices["shirt"] = 30'000;

	// for(auto it = prices.begin(); it != prices.end(); ++it) {
	for(const auto& [k,v]: prices) {
		std::cout << k << '\t' << v << '\n';
	}

	if(prices.count("book") == 1) {
		std::cout << "Book is in prices\n";
	}
	if(prices.count("paper") == 0) {
		std::cout << "Paper is not in prices\n";
	}
	return 0;
}
