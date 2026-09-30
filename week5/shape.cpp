#include <iostream>
class Shape {
public:
	virtual void draw() const = 0;
	virtual ~Shape() {
		std::cout << "Destructor of Shape\n";
	}
};

class Circle : public Shape {
private:
	int* ptr;
public:
	Circle() {
		ptr = new int[50];
	}
	void draw() const override {
		std::cout << "Draw a circle\n";
	}
	~Circle() override {
		delete[] ptr;
		std::cout << "Destructor of Circle\n";
	}
};

int main() {
	Shape* shape = new Circle;
	shape->draw();
	delete shape;
	return 0;
}
