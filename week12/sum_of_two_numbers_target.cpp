#include <iostream>
#include <vector>
#include <unordered_set>

bool check_sum_of_numbers(const std::vector<int>& numbers, int target) {
	for(int i = 0; i < numbers.size(); i++) {
		for(int j = i; j < numbers.size(); j++) {
			if(numbers[i] + numbers[j] == target) {
				return true;
			}
		}
	}
	return false;
}

bool check_sum_of_numbers_hash(const std::vector<int>& numbers, int target) {
	std::unordered_set<int> set(numbers.begin(), numbers.end());
	for(int i = 0; i < numbers.size(); i++) {
		if(set.count(target - numbers[i]) != 0) {
			return true;
		}
	}
	return false;
}

int main() {
	std::vector<int> numbers;
	int n_numbers;
	std::cin >> n_numbers;
	for(int i = 0; i < n_numbers; i++) {
		int num;
		std::cin >> num;
		numbers.push_back(num);
	}

	int target;
	std::cin >> target;

	if(check_sum_of_numbers(numbers, target)) {
		std::cout << "Yes!\n";
	} else {
		std::cout << "No!\n";
	}

	return 0;
}
