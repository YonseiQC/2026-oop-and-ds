#include <utility>
#include <iostream>

template<typename T>
struct Node {
	T value;
	Node<T>* left;
	Node<T>* right;
};

template <typename T>
Node<T>* create_leaf_node() {
	auto node = new Node<T>;
	// node->value has a trash value
	node->left = nullptr;
	node->right = nullptr;
	return node;
}

template<typename Func>
class TreeTraversaler;

template<typename T>
bool is_leaf(Node<T>* node) {
	return (node->left == nullptr) && (node->right == nullptr);
}

template<typename T>
class BinarySearchTree {
private:
	Node<T>* root_;

public:
	BinarySearchTree() {
		root_ = new Node<T>();
		root_->left = nullptr;
		root_->right = nullptr;
	}

	Node<T>* root() {
		return root_;
	}

	void push(T value) {
		Node<T>* node = root_;
		while(!is_leaf(node)) {
			if(value < node->value) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		node->value = value;
		node->left = create_leaf_node<T>();
		node->right = create_leaf_node<T>();
	}

	bool find_elt(T value) {
		Node<T>* node = root_;
		while(!is_leaf(node)) {
			if(node->value == value) {
				return true;
			}
			if(value < node->value) {
				node = node->left;
			} else {
				node = node->right;
			}
		}
		return false;
	}

	bool remove_elt(T value) {
		// Homework
		// return false if an element with `value` does not exist
	}

	~BinarySearchTree() {
		TreeTraversaler traversaler([](Node<T>* node) {
			delete node;
		});
		traversaler.postorder(root_);
	}
};

template<typename Func>
class TreeTraversaler {
private:
	Func visitor_;
public:
	TreeTraversaler(Func&& visitor)
		: visitor_(std::forward<Func>(visitor)){
	}

	template<typename T>
	void postorder(Node<T>* node) {
		if (node == nullptr) {
			return ;
		}
		postorder(node->left);
		postorder(node->right);
		visitor_(node);
	}

	template<typename T>
	void preorder(Node<T>* node) {
		if (node == nullptr) {
			return ;
		}
		visitor_(node);
		preorder(node->left);
		preorder(node->right);
	}

	template<typename T>
	void inorder(Node<T>* node) {
		if (node == nullptr) {
			return ;
		}
		inorder(node->left);
		visitor_(node);
		inorder(node->right);
	}
};

int main() {
	BinarySearchTree<int> btree;

	TreeTraversaler traversaler([](Node<int>* node){
		if (!is_leaf(node)) {
			std::cout << node->value << '\n';
		}
	});

	btree.push(30);
	btree.push(10);
	btree.push(26);
	btree.push(38);
	btree.push(55);

	traversaler.inorder(btree.root()); // we obtain a sorted array

	return 0;
}
