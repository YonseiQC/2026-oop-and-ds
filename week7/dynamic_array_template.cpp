#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <memory>

template <typename T>
class DynamicArray {
private:
	std::unique_ptr<T[]> ptr_;
	int length_;
	int capacity_;

	void double_size() {
		std::unique_ptr<T[]> new_ptr = std::make_unique<T[]>(2 * capacity_);
		for(int i = 0; i < length_; i++) {
			new_ptr[i] = ptr_[i];
		}
		ptr_ = std::move(new_ptr);
		capacity_ *= 2;
	}

public:
	explicit DynamicArray(int capacity = 16) : length_(0), capacity_(capacity) {
		ptr_ = std::make_unique<T[]>(capacity);
	}

	DynamicArray(const DynamicArray& other) { // copy constructor
		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = new T[capacity_];
		std::copy(other.ptr_, other.ptr_ + length_, ptr_);
		// Don't forget to initialize all member variables!!
	}

	T* begin() {
		return ptr_;
	}

	T* end() {
		return ptr_ + length_;
	}

	const T* begin() const {
		return ptr_;
	}

	const T* end() const {
		return ptr_ + length_;
	}

	// Copy assignment operator
	DynamicArray& operator=(const DynamicArray<T>& other) {
		if(this == &other)
			return *this;
		delete[] ptr_;

		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = new T[capacity_];
		std::copy(other.ptr_, other.ptr_ + length_, ptr_);
		// Don't forget to assign all member variables!!
		return *this;
	}

	int get_capacity() const {
		return capacity_;
	}

	int get_length() const {
		return length_;
	}

	void add_elt(const T& val) {
		if (length_ == capacity_) {
			double_size();
		}
		ptr_[length_++] = val;
	}

	T& operator[](size_t idx) {
		return ptr_[idx];
	}

	const T& operator[](size_t idx) const {
		return ptr_[idx];
	}

	using iterator = T*;
	using const_iterator = const T*;
};
/* Encapsulation */

int main() {
	DynamicArray<int> arr(10); // make dynamic array with capacity = 10
						  //
	for (int i = 0; i < 100; i++) {
		arr.add_elt(i);
	}

	for(auto val: arr) {
		std::cout << val << ',';
	}

	std::transform(std::begin(arr), std::end(arr), std::begin(arr), [](int val) {
		return val + 10;
	});
	return 0;
}
