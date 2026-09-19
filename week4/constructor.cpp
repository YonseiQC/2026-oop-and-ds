#include <iostream>

class Counter {
private:
    int value_ = 0;
public:
    Counter() = default;
    explicit Counter(int initial_value) : value_(initial_value) {}
	int get_count() const {
		return value_;
	}
};

void print_counter(const Counter& counter) {
	std::cout << counter.get_count() << '\n';
}

int main() {
	// Without explicit, the following line works
	// print_counter(10);
	print_counter(Counter(10));
	return 0;
}
