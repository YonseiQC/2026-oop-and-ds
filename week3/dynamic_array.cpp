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
	DynamicArray(int capacity = 16) : length_(0), capacity_(capacity) {
		ptr_ = (int*)malloc(sizeof(int) * capacity);
	}

	DynamicArray(const DynamicArray& other) {
		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = (int*)malloc(sizeof(int) * capacity_);
		std::copy(other.ptr_, other.ptr_ + length_, ptr_);
		// Don't forget to initialize all member variables!!
	}

	DynamicArray& operator=(const DynamicArray& other) {
		free(ptr_);

		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = (int*)malloc(sizeof(int) * capacity_);
		std::copy(other.ptr_, other.ptr_ + length_, ptr_);
		// Don't forget to initialize all member variables!!
		return *this;
	}

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

	~DynamicArray() {
		free(ptr_);
	}
};
/* Encapsulation */

int main() {
	DynamicArray arr(10); // make dynamic array with capacity = 10
	
	DynamicArray arr2 = arr; // calling a copy constructor
	
	DynamicArray arr3 = arr2;
	arr3 = arr2; // calling a copy assignment operator
	
	std::cout << "arr2[0]: " << arr2.get_elt(0) << '\n';
	arr3.add_elt(3); // This must not change arr2
	std::cout << "arr2[0]: " << arr2.get_elt(0) << '\n';

	arr3 = arr2 = arr;

	/*
	std::cout << arr.get_capacity() << '\n'; // prints 10
	for(int i = 0; i < 100; i++) {
		arr.add_elt(i);
	}

	for(int i = 0; i < 100; i++) {
		std::cout << arr.get_elt(i) << '\t';
	}
	std::cout << "New capacity: " << arr.get_capacity() << '\n';
	std::cout << '\n';
	*/

	return 0;
}
