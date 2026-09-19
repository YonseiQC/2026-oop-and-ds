#include <cstdlib>
#include <iostream>

class DynamicArray {
private:
	int* ptr_;
	int length_;
	int capacity_;

	void double_size() {
		int* new_ptr = (int*)malloc(sizeof(int) * 2 * capacity_);
		for(int i = 0; i < length_; i++) {
			new_ptr[i] = ptr_[i];
		}
		ptr_ = new_ptr;
		capacity_ *= 2;
	}

public:
	int get_capacity() {
		return capacity_;
	}

	int get_length() {
		return length_;
	}

	void add_elt(int val) {
		if (length_ == capacity_) {
			double_size();
		}
		ptr_[length_++] = val;
	}

	int get_elt(int idx) {
		return ptr_[idx];
	}

	DynamicArray(int capacity = 16) : length_(0), capacity_(capacity) {
		ptr_ = (int*)malloc(sizeof(int) * capacity);
	}

	~DynamicArray() {
		free(ptr_);
	}
};
/* Encapsulation */

int main() {
	DynamicArray arr(10); // make dynamic array with capacity = 10
	std::cout << arr.get_capacity() << '\n'; // prints 10
	for(int i = 0; i < 100; i++) {
		arr.add_elt(i);
	}

	for(int i = 0; i < 100; i++) {
		std::cout << arr.get_elt(i) << '\t';
	}
	std::cout << "New capacity: " << arr.get_capacity() << '\n';
	std::cout << '\n';

	return 0;
}
