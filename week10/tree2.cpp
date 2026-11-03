#include <vector>
#include <stdexcept>
#include <iostream>
#include <format>
#include <stack>
#include <ranges>
#include <queue>

template<typename T> class Node; // Forward declaration

template<typename T>
class Tree {
private:
	std::vector<Node<T>*> all_nodes_;

public:
	Tree() {
	}

	int size() const {
		return all_nodes_.size();
	}

	bool is_empty() const {
		return all_nodes_.empty();
	}

	const Node<T>* root() const {
		if(is_empty()) {
			throw std::out_of_range("The tree is empty");
		}
		return all_nodes_[0];
	}

	const std::vector<Node<T>*>& all_nodes() const {
		return all_nodes_;
	}

	Node<T>* add_node(Node<T>* parent, const T& elt) {
		Node<T>* node = new Node<T>(elt, parent);
		all_nodes_.push_back(node);
		if(parent != nullptr) {
			// if not a root node
			parent->add_child(node);
		}
		return node;
	}

	~Tree() {
		for(auto node: all_nodes_) {
			delete node;
		}
	}
};

template<typename T>
class Node {
private:
	T elt_;
	Node* parent_;
	std::vector<Node*> children_;

public:
	Node(const T& elt, Node* parent) : elt_(elt), parent_(parent) {
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

	Node* parent() const {
		return parent_;
	}

	const std::vector<Node*>& children() const {
		return children_;
	}

	void add_child(Node* child) {
		children_.push_back(child);
	}

	bool is_root() const {
		return parent_ == nullptr;
	}

	bool is_external() const {
		return children_.size() == 0;
	}
};


template<typename Node>
int depth(const Node* node) {
	if(node->is_root()) {
		return 0;
	}
	return 1 + depth(node->parent());
}

template<typename Tree>
int height1(const Tree& tree) {
	int h = 0;
	for(const auto node: tree.all_nodes()) {
		if(node->is_external()) {
			int d = depth(node);
			if(h < d) {
				h = d;
			}
		}
	}
	return h;
}

template<typename Tree, typename Node>
int height2(const Tree& tree, const Node* p) {
	if(p->is_external()) {
		return 0;
	}
	int h = 0;
	for(const auto child: p->children()) {
		h = std::max(h, height2(tree, child));
	}
	return h + 1;
}

template<typename T>
void to_parenthetic_str(const Node<T>* p, int depth) {
	for(int i = 0; i < depth; i++)
		std::cout << '\t';
	std::cout << std::format("{} ", p->get());
	if(p->is_external()) {
		std::cout << "\n";
	} else {
		std::cout << "(\n";
		for(const auto* child: p->children()) {
			preorder(child, depth + 1);
		}
		for(int i = 0; i < depth; i++)
			std::cout << '\t';
		std::cout << ")\n";
	}
}

template<typename T>
void preorder(const Node<T>* p) {
	std::cout << std::format("Visiting {}\n", p->get());
	for(const auto* child: p->children()) {
		preorder(child);
	}
}

template<typename T>
void postorder(const Node<T>* p) {
	for(const auto* child: p->children()) {
		postorder(child);
	}
	std::cout << std::format("Visiting {}\n", p->get());
}

template<typename T>
void preorder_stack(const Node<T>* p) {
	std::stack<const Node<T>*> st;
	st.push(p);
	while(!st.empty()) {
		const auto* node = st.top();
		st.pop();
		std::cout << std::format("Visiting {}\n", node->get());
		for(const auto* child: node->children() | std::views::reverse) {
			st.push(child);
		}
	}
}

template<typename T>
void bfs(const Node<T>* p) {
	std::queue<const Node<T>*> q;
	q.push(p);
	while(!q.empty()) {
		const auto* node = q.front();
		q.pop();
		std::cout << std::format("Visiting {}\n", node->get());
		for(const auto* child: node->children()) {
			q.push(child);
		}
	}
}

int main() {
	Tree<std::string> tree;
	auto root = tree.add_node(nullptr, "Electronics R\' Us");
	auto r_and_d = tree.add_node(root, "R&D");
	auto sales = tree.add_node(root, "Sales");
	auto purchasing = tree.add_node(root, "Purchasing");
	auto manufacturing = tree.add_node(root, "Manufacturing");

	auto domestic = tree.add_node(sales, "Domestic");
	auto international = tree.add_node(sales, "International");

	auto canada = tree.add_node(international, "Canada");
	auto s_america = tree.add_node(international, "S. America");
	auto overseas = tree.add_node(international, "Overseas");

	auto africa = tree.add_node(overseas, "Africa");
	auto europe = tree.add_node(overseas, "Europe");
	auto asia = tree.add_node(overseas, "Asia");
	auto australia = tree.add_node(overseas, "Australia");

	auto tv = tree.add_node(manufacturing, "TV");
	auto cd = tree.add_node(manufacturing, "cd");
	auto tuner = tree.add_node(manufacturing, "Tuner");

	postorder(tree.root());
	return 0;
}
