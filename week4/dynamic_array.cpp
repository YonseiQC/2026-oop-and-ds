#include <cstdlib>
#include <iostream>
#include <vector>

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
	int get_capacity() const {
		return capacity_;
	}

	int get_length() const {
		return length_;
	}

	void add_elt(int val) {
		if (length_ == capacity_) {
			double_size();
		}
		ptr_[length_++] = val;
	}

	inline const int& operator[](int idx) const {
		return ptr_[idx];
	}

	inline int& operator[](int idx) {
		return ptr_[idx];
	}

	explicit DynamicArray(int capacity = 16) : length_(0), capacity_(capacity) {
		ptr_ = (int*)malloc(sizeof(int) * capacity);
	}

	~DynamicArray() {
		free(ptr_);
	}
};

std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const DynamicArray& arr) {
	os << '[';
	for(int i = 0; i < arr.get_length(); i++) {
		if(i != arr.get_length()-1) {
			os << arr[i] << ", ";
		} else {
			os << arr[i];
		}
	}
	os << ']';
	return os;
}

/* Encapsulation */
int main() {
	DynamicArray arr(10); // make dynamic array with capacity = 10
	std::cout << arr.get_capacity() << '\n'; // prints 10
	for(int i = 0; i < 100; i++) {
		arr.add_elt(i);
	}

	std::cout << "New capacity: " << arr.get_capacity() << '\n';
	std::cout << '\n';

	std::cout << arr << '\n';

	return 0;
}
