#include <string>
#include <format>
#include <iostream>

class Bird {
private:
	std::string name_;
public:
	Bird(const std::string& name) : name_{name} {}
	virtual void quark() const = 0;
	void fly() const {
		std::cout << std::format("Flying {}\n", name_);
	}
};

class Parrot: public Bird {
public:
	Parrot() : Bird("Parrot") {}

	void quark() const override {
		std::cout << "PARROTT\n";
	}
};

class Ostrich : public Bird {
public:
	Ostrich() : Bird("Ostrich") {}

	void quark() const override {
		std::cout << "TAZZOO\n";
	}
};

int main() {
	Ostrich* instance = new Ostrich;

	instance->quark();
	instance->fly();

	Parrot* parrot = new Parrot;
	parrot->quark();
	parrot->fly();

	return 0;
}
