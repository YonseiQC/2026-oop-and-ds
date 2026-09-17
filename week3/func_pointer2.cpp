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
	using fptr_t = int (*)(int, int); 
	// or
	// typedef int (*ptr_t)(int, int);
	fptr_t ptr = sum;
	fptr_t* ptr2 = &ptr;
	*ptr2 = sum2; // ptr now points sum2
	std::cout << (*ptr)(3, 4) << '\n'; // prints 10
	
	using fptr2_t = double (*)(fptr_t, double);
	fptr2_t ptr3  = func;
	fptr2_t *ptr_arr4[] = {&ptr3}; // array of pointer
	//fptr2_t (*ptr_arr5)[]; // pointer to array
	
	return 0;
}
