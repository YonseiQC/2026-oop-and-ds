#include <string>
#include <format>
#include <iostream>

struct Node {
	std::string data;
	Node* next;
};
class SinglyLinkedList {
private:
	Node* head_;
	Node* tail_;
	int size_;
public:
	SinglyLinkedList() {
		head_ = nullptr;
		tail_ = nullptr;
		size_ = 0;
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
		-- size_;

		if(head_ == nullptr) {
			tail_ = nullptr;
		}
	}

	void push_back(const std::string& data) {
		auto node = new Node;
		node->data = data;
		node->next = nullptr;
		tail_->next = node;
		if(head == nullptr) {
			head_ = node;
		}
		++size_;
	}

	const std::string back() const {
		return tail_->data;
	}

	void pop_back() {
		if(is_empty()) {
			// do nothing if empty
			return ;
		}
		Node* ptr = head_;
		while(ptr->next != tail_) {
			ptr = ptr->next;
		}
		Node* old_tail = tail_;
		tail_ = ptr;
		delete old_tail;
		tail_->next = nullptr;
	}

	void push_front(const std::string& data) {
		auto node = new Node;
		node->data = data;
		node->next = head_;
		head_ = node;
		if(tail_ == nullptr) {
			tail_ = node;
		}
		++ size_;
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
		++size_;
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
		--size_;
	}

	int length() const {
		return size_;
	}

	~SinglyLinkedList() {
		while(!is_empty()) {
			pop_front();
		}
	}
};

int main() {
	SinglyLinkedList list;
	for(int i = 0; i < 10; i++) {
		list.push_front(std::format("{} is added", i));
	}

	// Warning: This code is slow!
	// We will introduce iterator later for the solution
	for(int i = 0; i < list.length(); i++) {
		std::cout << std::format("{}-th element is \"{}\"\n", i, list.get_data(i));
	}

	// We now add an element on the middle of the list
	std::cout << "Adding an element at index 5 \n";
	list.insert(5, "The last element");
	for(int i = 0; i < list.length(); i++) {
		std::cout << std::format("{}-th element is \"{}\"\n", i, list.get_data(i));
	}
	return 0;
}
