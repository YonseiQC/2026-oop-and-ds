#include <iostream>
#include <vector>

// Generate all possible combination choosing k elements from the given array
class CombinationGenerator {
private:
	std::vector<int> arr_;

	std::vector<std::vector<int>> res_;

	void all_comb(int n, int k, std::vector<int>& tmp) {
		// No combination exists (also prevents reading arr_[-1])
		if (k < 0 || k > n) {
			return ;
		}

		// tmp holds the chosen elements in descending order, so reverse it
		if (k == 0) {
			res_.emplace_back(tmp.rbegin(), tmp.rend());
			return ;
		}

		// We choose the last element from the array
		tmp.push_back(arr_[n-1]);
		all_comb(n-1, k-1, tmp);
		tmp.pop_back();

		// We do not choose the last element from the array
		all_comb(n-1, k, tmp);
	}

public:
	CombinationGenerator(const std::vector<int>& arr, int k)
		: arr_(arr) {
		std::vector<int> tmp;
		all_comb(static_cast<int>(arr_.size()), k, tmp);
	}

	const std::vector<std::vector<int>>& result() const {
		return res_;
	}

};

int main() {
	CombinationGenerator comb_gen(std::vector<int>{1, 2, 3, 4, 5}, 3);

	for(const auto& arr: comb_gen.result()) {
		for(auto elt: arr) {
			std::cout << elt << '\t';
		}
		std::cout << '\n';
	}

	return 0;
}
