#include <iostream>
#include <stack>
#include <vector>
#include <tuple>

// Generate all possible combination choosing k elements from the given array
class CombinationGenerator {
private:
	std::vector<int> arr_;

	std::vector<std::vector<int>> res_;

	void all_comb(int k0) {
		std::stack<std::tuple<int, int, std::vector<int>>> st;

		st.emplace(static_cast<int>(arr_.size()), k0, std::vector<int>());
		while(!st.empty()) {
			auto [n, k, v] = std::move(st.top());
			st.pop();

			// No combination exists (also prevents reading arr_[-1])
			if (k < 0 || k > n) {
				continue;
			}

			if (k == 0) {
				// v holds the chosen elements in descending order, so reverse it
				res_.emplace_back(v.rbegin(), v.rend());
			} else {
				st.emplace(n-1, k, v); // do not choose the last element

				// And choose the last element
				v.push_back(arr_[n-1]);
				st.emplace(n-1, k-1, v);
			}
		}
	}

public:
	CombinationGenerator(const std::vector<int>& arr, int k)
		: arr_(arr) {
		all_comb(k);
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
