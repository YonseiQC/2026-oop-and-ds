#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

template<typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;
};

template<typename T>
class DoublyLinkedList {
private:
	Node<T>* dummy_;
	int size_;

	void remove_node(Node<T>* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		--size_;
	}

	// Add a node next to curr_node
	void add_node(Node<T>* curr_node, const T& data) {
		auto node = new Node<T>;
		node->data = data;
		node->prev = curr_node;
		node->next = curr_node->next;
		
		curr_node->next->prev = node;
		curr_node->next = node;

		++size_;
	}

public:
	DoublyLinkedList() {
		dummy_ = new Node<T>;
		dummy_->prev = dummy_;
		dummy_->next = dummy_;

		size_ = 0;
	}

	// The list owns its nodes, so copying would free them twice
	DoublyLinkedList(const DoublyLinkedList&) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

	bool is_empty() const {
		return (dummy_->prev == dummy_);
	}

	T front() const {
		if (is_empty()) {
			// raise an error
			throw std::out_of_range("The list is empty");
		}
		return dummy_->next->data;
	}

	void pop_front() {
		if (is_empty()) {
			throw std::out_of_range("The list is empty");
		}
		remove_node(dummy_->next);
	}

	void push_front(const T& data) {
		add_node(dummy_, data);
	}

	T back() const {
		if (is_empty()) {
			throw std::out_of_range("The list is empty");
		}
		return dummy_->prev->data;
	}

	void pop_back() {
		if (is_empty()) {
			// if dummy is the only element
			throw std::out_of_range("The list is empty");
		}
		remove_node(dummy_->prev);
	}

	void push_back(const T& data) {
		add_node(dummy_->prev, data);
	}

	T get_data(int idx) const {
		if(idx < 0 || idx >= size_) {
			throw std::out_of_range("The index is out of the range");
		}
		if (idx < size_/2) {
			Node<T>* ptr = dummy_->next;
			while(idx > 0) {
				ptr = ptr->next;
				--idx;
			}
			return ptr->data;
		} else {
			Node<T>* ptr = dummy_->prev;
			while(idx < size_ - 1) {
				ptr = ptr->prev;
				++idx;
			}
			return ptr->data;
		}
	}

	int length() const {
		return size_;
	}

	void merge(DoublyLinkedList<T>& rhs) {
		// Merging a list into itself would lose all of its nodes
		if(&rhs == this || rhs.is_empty()) {
			return ;
		}

		auto this_tail = dummy_->prev;

		auto that_head = rhs.dummy_->next;
		auto that_tail = rhs.dummy_->prev;

		this_tail->next = that_head;
		that_head->prev = this_tail;
		this->dummy_->prev = that_tail;
		that_tail->next = this->dummy_;

		this->size_ += rhs.size_;

		rhs.dummy_->prev = rhs.dummy_;
		rhs.dummy_->next = rhs.dummy_;
		rhs.size_ = 0;
	}

	~DoublyLinkedList() {
		while(!is_empty()) {
			pop_front();
		}
		delete dummy_;
	}
};

int main() {

	// Let's make some test
	{
		// Testing push_front and pop_front
		DoublyLinkedList<int> list;
		for(int i = 0; i < 100; i++) {
			list.push_front(i);
		}

		for(int k = 0; k < 100; k++) {
			assert(list.get_data(k) == 99-k);
		}

		for(int k = 99; k >=0; --k) {
			assert(list.front() == k);
			list.pop_front();
		}
	}
	{
		// Testing push_back and pop_back
		DoublyLinkedList<int> list;
		for(int i = 0; i < 100; i++) {
			list.push_back(i);
		}

		for(int k = 0; k < 100; k++) {
			assert(list.get_data(k) == k);
		}

		for(int k = 99; k >=0; --k) {
			assert(list.back() == k);
			list.pop_back();
		}
	}
	{
		// Testing a bit more complicated thing 
		DoublyLinkedList<int> list;
		list.push_back(0);
		list.push_front(1);
		list.push_back(2);
		list.push_front(3);

		list.pop_back();
		list.pop_front();

		assert(list.length() == 2);
		assert(!list.is_empty());
		assert(list.front() == 1);
		assert(list.back() == 0);
	}


	{
		// Testing merging two doubly linked list
		DoublyLinkedList<int> list1, list2;

		for(int i = 0; i < 3; i++) {
			list1.push_back(i);
			list2.push_back(3 + i);
		}

		list1.merge(list2);

		assert(list2.is_empty());
		assert(list1.length() == 6);

		for(int i = 0; i < 6; i++) {
			assert(list1.get_data(i) == i);
		}
	}

	return 0;
}
