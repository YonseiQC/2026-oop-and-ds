#include <iostream>
#include <list>
#include <stdexcept>
#include <format>
#include <functional>

struct Point {
	double x;
	double y;
};

bool compare_x_first(const Point& p1, const Point& p2) {
	if(p1.x < p2.x) {
		return true;
	} 
	if(p1.x > p2.x) {
		return false;
	}
	if(p1.y < p2.y) {
		return true;
	}
	return false;
}

bool compare_y_first(const Point& p1, const Point& p2) {
	if(p1.y < p2.y) {
		return true;
	} 
	if(p1.y > p2.y) {
		return false;
	}
	if(p1.x < p2.x) {
		return true;
	}
	return false;
}

template<typename T>
class PriorityQueue {
private:
	std::list<T> list_;
	std::function<bool(const T&, const T&)> func_to_compare_;

public:
	PriorityQueue(std::function<bool(const T&, const T&)> func_to_compare)
		: func_to_compare_(func_to_compare) {
	}

	void push(T elt) {
		auto it = list_.cbegin();
		for(;it != list_.cend(); ++it) {
			if(func_to_compare_(*it, elt)) {
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
	auto func = [](const Point& p1, const Point& p2) -> bool {
		return (p1.x*p1.x + p1.y*p1.y) < (p2.x*p2.x + p2.y*p2.y);
	};
	PriorityQueue<Point> pq(func);
	pq.push(Point{3.0, 2.0});
	pq.push(Point{-1.0, 3.0});
	pq.push(Point{2.0, 4.0});
	pq.push(Point{1.0, 8.0});
	pq.push(Point{1.0, 7.0});

	while(!pq.is_empty()) {
		Point p = pq.top();
		std::cout << std::format("x: {}, y: {}", p.x, p.y) << '\n'; pq.pop();
	}

	return 0;
}
