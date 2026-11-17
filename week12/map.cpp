#include <map>
#include <string>
#include <format>
#include <iostream>

int main() {
	std::map<std::string, int> prices;
	prices["GPU"] = 1'000'000;
	prices["CPU"] = 100'000;
	prices["memory"] = 100'000;

	for(auto it = prices.begin(); it != prices.end(); ++it) {
		std::cout << std::format("key: {}, value: {}\n", it->first, it->second);
	}
	return 0;
}
