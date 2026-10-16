#include <iostream>
class Parent {
public:
    void function() {
        std::cout << "Parent\n";
    }
};
class Child : public Parent {
public:
    void function() {
        std::cout << "Child\n";
    }
};
int main() {
    Parent* p = new Child();
    p->function();
	return 0;
}
