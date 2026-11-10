#include <vector>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <format>

template<typename T>
class CompleteTree {
private:
	std::vector<T> elts_;

public:
	int size() const {
		return elts_.size();
	}

	static int parent_of(int idx) {
		return (idx-1)/2;
	}

	static int left_child_idx(int idx) {
		return 2*idx + 1;
	}

	static int right_child_idx(int idx) {
		return 2*idx + 2;
	}

	bool has_left_child(int idx) const {
		return 2*idx+1 < size();
	}

	bool has_right_child(int idx) const {
		return 2*idx+2 < size();
	}

	bool is_root(int idx) const {
		return idx == 0;
	}

	int root() const {
		if(size() == 0) {
			throw std::out_of_range("The tree is empty");
		}
		return elts_[0];
	}

	void add_last(const T& val) {
		elts_.push_back(val);
	}

	void remove_last() {
		elts_.pop_back();
	}

	void swap(int idx1, int idx2) {
		std::swap(elts_[idx1], elts_[idx2]);
	}

	T& operator[](int idx) {
		return elts_[idx];
	}

	const T& operator[](int idx) const {
		return elts_[idx];
	}
};

template<typename T>
class Heap {
private:
	CompleteTree<T> t_;
	std::function<bool(const T&, const T&)> comp_;

public:
	template <typename U>
	Heap(U&& comp) : comp_(comp) {}
	// Heap(std::function<bool(const T&, const T&)> comp) : comp_(comp) {}
	int size() const {
		return t_.size();
	}

	bool is_empty() const {
		return size() == 0;
	}

	T& push(T elt) {
		int idx = t_.size();
		t_.add_last(elt);
		while(!t_.is_root(idx)) {
			int parent = t_.parent_of(idx);
			if(comp_(t_[parent], t_[idx])) {
				break;
			}
			t_.swap(idx, parent);
			idx = parent;
		}
		return t_[idx];
	}

	T top() const {
		return t_.root();
	}

	void pop() {
		if(is_empty()) {
			throw std::out_of_range("The heap is empty");
		}
		int last_idx = t_.size() - 1;
		t_.swap(0, last_idx);
		t_.remove_last();

		int idx = 0;
		while(t_.has_left_child(idx)) {
			int left_child_idx = t_.left_child_idx(idx);
			int smaller_child_idx = left_child_idx;
			if(t_.has_right_child(idx)) {
				// If initializer
				if(int right_child_idx = t_.right_child_idx(idx);
						comp_(t_[right_child_idx], t_[smaller_child_idx])) {
					smaller_child_idx = right_child_idx;
				}
			}
			if(comp_(t_[smaller_child_idx], t_[idx])) {
				t_.swap(smaller_child_idx, idx);
				idx = smaller_child_idx;
			} else {
				break;
			}
		}
	}

	T get_elt(int idx) const {
		return t_[idx];
	}
};

int main() {
	Heap<std::pair<int, std::string>> heap(
		[](const std::pair<int, std::string>& lhs, const std::pair<int, std::string>& rhs)-> bool {
			return lhs.first < rhs.first;
		});
	heap.push(std::make_pair(3, "Face injury"));
	heap.push(std::make_pair(5, "Cold"));
	heap.push(std::make_pair(1, "Almost dying"));
	heap.push(std::make_pair(6, "Perfectly normal"));

	for(int i = 0; i < heap.size(); i++) {
		const auto [priority, value] = heap.get_elt(i);
		std::cout << std::format("({},{})", priority, value) << '\t';
	}
	std::cout << '\n';

	return 0;
}
