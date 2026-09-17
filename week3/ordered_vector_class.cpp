#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

class OrderedArray {
private:
	std::vector<int> vec_;

public:
	void add_elt(int elt) {
		auto it = std::lower_bound(std::begin(vec_), std::end(vec_), elt);
		vec_.insert(it, elt);
	}

	bool find_elt(int elt) {
		return std::binary_search(std::begin(vec_), std::end(vec_), elt);
	}
};

int main() {
	OrderedArray ordered_arr;

	// The following is the basic scheme to generate pseudorandom numbers
	std::mt19937 re{1557};
	std::cout << re() << '\n'; // generate a 32-bit integer
	std::uniform_int_distribution<int> dist(0, 100);

	for(int i = 0; i < 30; i++) {
		ordered_arr.add_elt(dist(re));
	}
	return 0;
}
