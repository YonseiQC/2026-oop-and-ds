#include <stdexcept>
#include <string>
#include <format>
#include <iostream>
#include <vector>

class Transport {
private:
	std::string name_;
	int max_num_items_;
	int max_weight_per_items_; // in kg
public:
	Transport(std::string name, int max_num_items, int max_weight_per_items) 
		: name_{std::move(name)}, max_num_items_{max_num_items}, max_weight_per_items_{max_weight_per_items} {
		// We may define types to reduce confusions
	}
	std::string name() const {
		return name_;
	}
	std::string desc() const {
		return std::format("Name: {}\nMaximum number of items: {}\nMaximum weight per items: {}", name_, max_num_items_, max_weight_per_items_);
	}
};

class Boat : public Transport {
public:
	Boat() : Transport("Boat", 10'000, 10'000){
	}
};

class Bike: public Transport {
public:
	Bike() : Transport("Bike", 3, 10){
	}
};

class Truck: public Transport {
public:
	Truck() : Transport("Truck", 100, 100){
	}
};

class USATruck: public Transport {
public:
	USATruck() : Transport("USATruck", 10'000, 100){
	}
};

class Creator {
public:
	virtual Transport* create(const std::string& name) = 0;
};

class DefaultCreator : public Creator {
public:
	virtual Transport* create(const std::string& name) {
		if(name == "Boat") {
			return new Boat();
		}
		else if (name == "Bike") {
			return new Bike();
		}
		else if (name == "Truck") {
			return new Truck();
		}
		else {
			// Should not be reached
			throw std::invalid_argument("Name is not recognizable");
			return nullptr;
		}
	}
};

class USACreator : public Creator {
public:
	virtual Transport* create(const std::string& name) {
		if(name == "Boat") {
			return new Boat();
		}
		else if (name == "Bike") {
			return new Bike();
		}
		else if (name == "Truck") {
			return new USATruck();
		}
		else {
			// Should not be reached
			throw std::invalid_argument("Name is not recognizable");
			return nullptr;
		}
	}
};


int main() {
	auto* creator = new USACreator;
	auto* transport1 = creator->create("Truck");
	std::cout << transport1->desc() << '\n';
	delete transport1;

	std::vector<Transport*> transports;
	while(!std::cin.eof()) {
		std::string line;
		std::cin >> line;
		if(line.empty()) {
			break;
		}
		if (line[line.length()-1] == '\n') {
			line.erase(line.length()-1);
		}
		try {
			transports.emplace_back(creator->create(line));
		} catch(std::exception& e) {
			// exception should be caught by reference
			std::cout << e.what() << '\n';
		}
	}

	for(const auto* t: transports) {
		std::cout << t->desc() << '\n';
	}

	// memory free
	for(const auto* t: transports) {
		delete t;
	}

	delete creator;
	return 0;
}
