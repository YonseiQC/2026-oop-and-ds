#include <string>
#include <format>
#include <iostream>

class Bird {
public:
	virtual void quark() const = 0;
};

class Flyable {
private:
	std::string name_;
public:
	Flyable(const std::string& name) : name_(name) {}
	void fly() const {
		std::cout << std::format("Flying {}\n", name_);
	}
};

class Parrot: public Bird, public Flyable {
public:
	Parrot() : Flyable("Parrot") {}

	void quark() const override {
		std::cout << "PARROTT\n";
	}
};

class Ostrich : public Bird {
public:
	Ostrich() {}

	void quark() const override {
		std::cout << "TAZZOO\n";
	}
};

int main() {
	Ostrich* instance = new Ostrich;

	instance->quark();

	Parrot* parrot = new Parrot;
	parrot->quark();
	parrot->fly();

	return 0;
}
