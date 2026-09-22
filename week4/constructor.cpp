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

class Complex {
private:
	double real_;
	double imag_;

public:
	Complex(double real) : real_{real} {}
	Complex(double real, double imag) : real_{real}, imag_{imag} {}
};

Complex multiply_four(const Complex& val) {
	//
}

void print_counter(const Counter& counter) {
	std::cout << counter.get_count() << '\n';
}

int main() {
	Counter counter(20);
	counter.get_count() == 0;
	// Without explicit, the following line works
	// print_counter(10);
	print_counter(Counter(10));
	return 0;
}
