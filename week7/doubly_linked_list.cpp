#include <string>
#include <format>
#include <iostream>

struct Node {
	std::string data;
	Node* prev;
	Node* next;
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

	bool is_empty() const {
		return (head_ == nullptr);
	}

	const std::string front() const {
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
		head_ = node;

		if (tail_ == nullptr) {
			// If this is the only element
			tail_ = head_;
		}
	}

	const std::string back() const {
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
		// add your code here
	}

	std::string get_data(int idx) const {
		Node* ptr = head_;
		while(idx > 0) {
			ptr = ptr->next;
			--idx;
		}
		return ptr->data;
	}

	std::string& insert(int idx, const std::string& elt) {
		if (idx == 0) {
			push_front(elt);
		}
		Node* ptr = head_;
		while(idx > 1) {
			ptr = ptr->next;
			--idx;
		}
		Node* old_next = ptr->next;
		Node* new_node = new Node;
		new_node->data = elt;
		new_node->next = old_next;
		ptr->next = new_node;
		return new_node->data;
	}

	void remove(int idx) {
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
		ptr->next = ptr->next->next;
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
