#include <iostream>
int sum(int a, int b) {
	return a+b;
}
int sum2(int a, int b) {
	return 2*a + b;
}
double func(int (*ptr)(int, int), double a) {
	return ptr((int)a, (int)a);
}

int main() {
	int (*ptr)(int, int) = sum;
	int (**ptr2)(int, int) = &ptr; // double function pointer
	*ptr2 = sum2; // ptr now points sum2
	std::cout << (*ptr)(3, 4) << '\n'; // prints 10
	
	double (*ptr3)(int (*)(int,int), double) = func;
	double (**ptr_arr4[])(int (*)(int, int), double) = {&ptr3};
	
	return 0;
}
