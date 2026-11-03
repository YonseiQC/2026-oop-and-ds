#include <memory>
#include <vector>
#include <stdexcept>
#include <iostream>

template<typename T>
class Node {
private:
	T elt_;
	Node* left_;
	Node* right_;
public:
	Node(const T& elt) : elt_(elt) {
	}

	T& get() {
		return elt_;
	}

	const T& get() const {
		return elt_;
	}

	void set(const T& elt) {
		elt_ = elt;
	}

	void set_left(Node* node) {
		left_ = node;
	}

	void set_right(Node* node) {
		right_ = node;
	}

	const Node* left() const {
		return left_;
	}
	const Node* right() const {
		return right_;
	}

	Node* left() {
		return left_;
	}
	Node* right() {
		return right_;
	}

	bool is_external() const {
		return left_ == nullptr && right_ == nullptr;
	}
};

template<typename T>
void set_children(const std::vector<std::unique_ptr<T>>& nodes, int parent_idx, int left_child_idx, int right_child_idx) {
	nodes[parent_idx]->set_left(nodes[left_child_idx].get());
	nodes[parent_idx]->set_right(nodes[right_child_idx].get());
}

template<typename T>
void prefix(const Node<T>* node) {
	std::cout << node->get() << ' ';
	if(node->left() != nullptr) {
		prefix(node->left());
	}
	if(node->right() != nullptr) {
		prefix(node->right());
	}
}

template<typename T>
void postfix(const Node<T>* node) {
	if(node->left() != nullptr) {
		postfix(node->left());
	}
	if(node->right() != nullptr) {
		postfix(node->right());
	}
	std::cout << node->get() << ' ';
}

template<typename T>
void infix(const Node<T>* node) {
	if(node->left() != nullptr) {
		std::cout << '(';
		infix(node->left());
	}
	std::cout << node->get();
	if(node->right() != nullptr) {
		infix(node->right());
		std::cout << ')';
	}
}

// This is one of the simplest method to implement a binary tree
int main() {
	using StrNode = Node<std::string>;
	std::vector<std::unique_ptr<StrNode>> nodes;
	nodes.emplace_back(std::make_unique<StrNode>("-")); // 0
	nodes.emplace_back(std::make_unique<StrNode>("/")); // 1
	nodes.emplace_back(std::make_unique<StrNode>("+")); // 2
	nodes.emplace_back(std::make_unique<StrNode>("*")); // 3
	nodes.emplace_back(std::make_unique<StrNode>("+")); // 4
	nodes.emplace_back(std::make_unique<StrNode>("*")); // 5
	nodes.emplace_back(std::make_unique<StrNode>("6")); // 6
	nodes.emplace_back(std::make_unique<StrNode>("+")); // 7
	nodes.emplace_back(std::make_unique<StrNode>("3")); // 8
	nodes.emplace_back(std::make_unique<StrNode>("-")); // 9
	nodes.emplace_back(std::make_unique<StrNode>("2")); // 10
	nodes.emplace_back(std::make_unique<StrNode>("3")); // 11
	nodes.emplace_back(std::make_unique<StrNode>("-")); // 12
	nodes.emplace_back(std::make_unique<StrNode>("3")); // 13
	nodes.emplace_back(std::make_unique<StrNode>("1")); // 14
	nodes.emplace_back(std::make_unique<StrNode>("9")); // 15
	nodes.emplace_back(std::make_unique<StrNode>("5")); // 16
	nodes.emplace_back(std::make_unique<StrNode>("7")); // 17
	nodes.emplace_back(std::make_unique<StrNode>("4")); // 18
	
	set_children(nodes, 0, 1, 2);
	set_children(nodes, 1, 3, 4);
	set_children(nodes, 2, 5, 6);
	set_children(nodes, 3, 7, 8);
	set_children(nodes, 4, 9, 10);
	set_children(nodes, 5, 8, 9);
	set_children(nodes, 7, 13, 14);
	set_children(nodes, 9, 15, 16);
	set_children(nodes, 12, 17, 18);

	std::cout << "preorder: ";
	prefix(nodes[0].get());
	std::cout << '\n';

	std::cout << "inorder: ";
	infix(nodes[0].get());
	std::cout << '\n';

	std::cout << "postorder: ";
	postfix(nodes[0].get());
	std::cout << '\n';
	return 0;
}
