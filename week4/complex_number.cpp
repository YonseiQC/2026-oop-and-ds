#include <iostream>
#include <format>

class Complex {
public:
	// rule of zero
	Complex(double real, double imag = 0) : real_{real}, imag_{imag} {
	}
    Complex& operator+=(const Complex& rhs) {
        real_ += rhs.real_;
        imag_ += rhs.imag_;
        return *this;
    }
    Complex& operator-=(const Complex& rhs) {
        real_ -= rhs.real_;
        imag_ -= rhs.imag_;
        return *this;
    }

	Complex& operator*=(const Complex& rhs) {
		double new_real = real_*rhs.real_ - imag_*rhs.imag_;
		double new_imag = real_*rhs.imag_ + imag_*rhs.real_;
		real_ = new_real;
		imag_ = new_imag;
		return *this;
	}

	Complex& inverse() {
		double new_real = real_/(real_*real_ + imag_*imag_);
		double new_imag = -imag_/(real_*real_ + imag_*imag_);
		real_ = new_real;
		imag_ = new_imag;
		return *this;
	}

	Complex& operator/=(Complex rhs) {
		rhs.inverse();
		*this *= rhs;
		return *this;
	}

	double real() const {
		return real_;
	}
	double imag() const {
		return imag_;
	}

private:
    double real_ = 0.0;
    double imag_ = 0.0;
};

Complex operator+(Complex lhs, const Complex& rhs) {
	lhs += rhs;
	return lhs;
}

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& ss, const Complex& val) {
	ss << std::format("[{:.2f}+{:.2f}I]", val.real(), val.imag());
	return ss;
}

int main() {
	Complex val1(3.0, 4.0); // 3.0 + 4.0 I
	Complex val2(-2.8, 1.3); // -2.8 + 1.3 I
	
	Complex val = val1 + val2;

	std::cout << val << '\n';
	return 0;
}
