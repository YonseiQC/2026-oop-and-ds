#include <numeric>
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
public:

	// Nothing special of the class defined inside a class
	// Just the type name of this class would be SinglyLinkedList::Iterator
	class Iterator {
	private:
		Node* ptr_;
	public:
		Iterator(Node* ptr) : ptr_(ptr) {
		}

		Iterator& operator++() {
			// called when we use ++it;
			ptr_ = ptr_->next;
			return *this;
		}

		Iterator operator++(int dummy) {
			// int is a dummy argument
			// called when we use it++;
			Iterator it = *this;
			++*this;
			return it;
		}

		std::string& operator*() {
			return ptr_->data;
		}

		const std::string& operator*() const {
			return ptr_->data;
		}

		bool operator==(const Iterator& rhs) const {
			return (rhs.ptr_ == ptr_);
		}

		bool operator!=(const Iterator& rhs) const {
			return !(*this == rhs); // the same as "!this->operator==(rhs)"
		}
	};

	SinglyLinkedList() {
		head_ = nullptr;
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
	}

	void push_front(const std::string& data) {
		auto node = new Node;
		node->data = data;
		node->next = head_;
		head_ = node;
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

	int length() const {
		int n = 0;
		auto ptr = head_;
		while(ptr != nullptr) {
			ptr = ptr->next;
			++n;
		}
		return n;
	}

	Iterator begin() {
		return Iterator(head_);
	}
	Iterator end() {
		return Iterator(nullptr);
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

	int i = 0;
	for(auto it = list.begin(); it != list.end(); ++it) {
		std::cout << std::format("{}-th element is \"{}\"\n", i++, *it);
		// Now the complexity is O(n)
	}

	std::cout << "Using range-based for loop\n";
	// OR
	i = 0;
	for(auto val: list) {
		std::cout << std::format("{}-th element is \"{}\"\n", i++, val);
	}

	// We can even use some algorithms defined in the standard lib
	std::string concat = std::accumulate(list.begin(), list.end(), std::string(""));

	std::cout << concat << "\n";

	return 0;
}
