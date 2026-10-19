#include <string>
#include <iostream>
#include <stdexcept>

struct Node {
	std::string data;
	Node* prev = nullptr;
	Node* next = nullptr;
};

/*
 * The following code is incomplete. You should check 
 * the code and add your own implementation.
 */
class DoublyLinkedList {
private:
	Node* head_;
	Node* tail_;
public:
	DoublyLinkedList() {
		head_ = nullptr;
		tail_ = nullptr;
	}

	// The list owns its nodes, so copying would free them twice
	DoublyLinkedList(const DoublyLinkedList&) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

	bool is_empty() const {
		return (head_ == nullptr);
	}

	std::string front() const {
		if (is_empty()) {
			throw std::out_of_range("front() on empty list");
		}
		return head_->data;
	}

	void pop_front() {
		if(is_empty()) {
			// do nothing if empty
			return ;
		}
		auto ptr = head_;
		head_ = head_->next;
		delete ptr;
		if (head_ == nullptr) {
			tail_ = nullptr;
		}
		else {
			head_->prev = nullptr;
		}
	}

	void push_front(const std::string& data) {
		auto node = new Node;
		node->data = data;
		node->next = head_;
		node->prev = nullptr;

		if (head_ == nullptr) {
			// If this is the only element
			tail_ = node;
		}
		else {
			head_->prev = node;
		}
		head_ = node;
	}

	std::string back() const {
		if (is_empty()) {
			throw std::out_of_range("back() on empty list");
		}
		return tail_->data;
	}

	void pop_back() {
		if(is_empty()) {
			// do nothing if empty
			return ;
		}
		Node* old_tail = tail_;
		tail_ = tail_->prev;
		if(tail_ == nullptr) {
			head_ = nullptr;
			tail_ = nullptr;
		}
		else {
			tail_->next = nullptr;
		}
		delete old_tail;
	}

	void push_back(const std::string& data) {
		auto node = new Node;
		node->data = data;
		node->next = nullptr;
		node->prev = tail_;

		if (tail_ == nullptr) {
			// If this is the only element
			head_ = node;
		}
		else {
			tail_->next = node;
		}
		tail_ = node;
	}

	std::string get_data(int idx) const {
		if (idx < 0 || idx >= length()) {
			throw std::out_of_range("get_data() index out of range");
		}
		Node* ptr = head_;
		while(idx > 0) {
			ptr = ptr->next;
			--idx;
		}
		return ptr->data;
	}

	// Inserts elt so that it ends up at position idx (0 <= idx <= length())
	std::string& insert(int idx, const std::string& elt) {
		if (idx < 0 || idx > length()) {
			throw std::out_of_range("insert() index out of range");
		}
		if (idx == 0) {
			push_front(elt);
			return head_->data;
		}
		Node* ptr = head_;
		while(idx > 1) {
			ptr = ptr->next;
			--idx;
		}
		Node* old_next = ptr->next;
		Node* new_node = new Node;
		new_node->data = elt;
		new_node->prev = ptr;
		new_node->next = old_next;
		ptr->next = new_node;

		if (old_next == nullptr) {
			// Inserted at the end
			tail_ = new_node;
		}
		else {
			old_next->prev = new_node;
		}
		return new_node->data;
	}

	void remove(int idx) {
		if (idx < 0 || idx >= length()) {
			throw std::out_of_range("remove() index out of range");
		}
		if (idx == 0) {
			pop_front();
			return ;
		}
		Node* ptr = head_;
		while(idx > 1) {
			ptr = ptr->next;
			--idx;
		}

		auto node_to_remove = ptr->next;
		ptr->next = node_to_remove->next;

		if (node_to_remove->next == nullptr) {
			// Removed the last element
			tail_ = ptr;
		}
		else {
			node_to_remove->next->prev = ptr;
		}
		delete node_to_remove;
	}

	int length() const {
		int n = 0;
		Node* ptr = head_;
		while(ptr != nullptr) {
			ptr = ptr->next;
			++n;
		}
		return n;
	}

	~DoublyLinkedList() {
		while(!is_empty()) {
			pop_front();
		}
	}
};

int main() {
	return 0;
}
