#include <iostream>
#include <list>
#include <stdexcept>

template<typename T>
class PriorityQueue {
private:
	std::list<T> list_;

public:
	void push(T elt) {
		auto it = list_.cbegin();
		for(;it != list_.cend(); ++it) {
			if(*it < elt) {
				// we want to insert an element just before this element
				break;
			}
		}
		list_.insert(it, elt);
	}

	T top() const {
		if(is_empty()) {
			throw std::range_error("Cannot obtain top element from an empty PriorityQueue");
		}
		return list_.front();
	}
	void pop() {
		if(is_empty()) {
			throw std::range_error("Cannot obtain top element from an empty PriorityQueue");
		}
		return list_.pop_front();
	}

	bool is_empty() const {
		return list_.empty();
	}
};

int main() {
	PriorityQueue<int> pq;
	pq.push(10);
	pq.push(4);
	pq.push(18);
	pq.push(8);
	pq.push(12);

	while(!pq.is_empty()) {
		std::cout << pq.top() << '\n'; pq.pop();
	}

	return 0;
}
