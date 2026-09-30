#include <cstdlib>
#include <iostream>

class DynamicArrayConstIterator {
private:
	int* ptr_;
	int idx_;

public:
	DynamicArrayConstIterator(int* ptr, int idx)
		: ptr_{ptr}, idx_{idx} {
	}
	DynamicArrayConstIterator& operator++() {
		idx_ += 1;
		return *this;
	}

	DynamicArrayConstIterator& operator--(){
		idx_ += 1;
		return *this;
	}

	bool operator==(const DynamicArrayConstIterator& rhs) {
		return ptr_ == rhs.ptr_ && idx_ == rhs.idx_;
	}

	bool operator!=(const DynamicArrayConstIterator& rhs) {
		return !(*this == rhs);
	}

	const int& operator*() {
		return ptr_[idx_];
	}
};
class DynamicArrayIterator {
private:
	int* ptr_;
	int idx_;

public:
	DynamicArrayIterator(int* ptr, int idx)
		: ptr_{ptr}, idx_{idx} {
	}

	DynamicArrayIterator& operator++() {
		// called when ++it
		idx_ += 1;
		return *this;
	}

	DynamicArrayIterator operator++(int) {
		// called when it++
		DynamicArrayIterator it(*this);
		++(*this);
		return it;
	}

	DynamicArrayIterator& operator--(){
		// called when --it
		idx_ += 1;
		return *this;
	}

	DynamicArrayIterator operator--(int){
		// called when it--
		DynamicArrayIterator it(*this);
		--(*this);
		return it;
	}

	bool operator==(const DynamicArrayIterator& rhs) {
		return ptr_ == rhs.ptr_ && idx_ == rhs.idx_;
	}

	bool operator!=(const DynamicArrayIterator& rhs) {
		return !(*this == rhs);
	}

	int& operator*() {
		return ptr_[idx_];
	}
};

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
	explicit DynamicArray(int capacity = 16) : length_(0), capacity_(capacity) {
		ptr_ = new int[capacity];
	}

	DynamicArray(const DynamicArray& other) { // copy constructor
		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = new int[capacity_];
		std::copy(other.ptr_, other.ptr_ + length_, ptr_);
		// Don't forget to initialize all member variables!!
	}

	~DynamicArray() {
		delete[] ptr_;
	}

	int* begin() {
		return ptr_;
	}

	int* end() {
		return ptr_ + length_;
	}

	const int* begin() const {
		return ptr_;
	}

	const int* end() const {
		return ptr_ + length_;
	}

	// Copy assignment operator
	DynamicArray& operator=(const DynamicArray& other) {
		if(this == &other)
			return *this;
		delete[] ptr_;

		length_ = other.length_;
		capacity_ = other.capacity_;
		ptr_ = new int[capacity_];
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

	void add_elt(int val) {
		if (length_ == capacity_) {
			double_size();
		}
		ptr_[length_++] = val;
	}

	int& operator[](size_t idx) {
		return ptr_[idx];
	}

	const int& operator[](size_t idx) const {
		return ptr_[idx];
	}

	using iterator = DynamicArrayIterator;
	using const_iterator = DynamicArrayConstIterator;
};
/* Encapsulation */

int main() {
	DynamicArray arr(10); // make dynamic array with capacity = 10
						  //
	for (int i = 0; i < 100; i++) {
		arr.add_elt(i);
	}

	for(auto val: arr) {
		std::cout << val << ',';
	}

	std::transform(std::begin(arr), std::end(arr), std::begin(arr), [](int val) {
		return val + 10;
	})
	return 0;
}
