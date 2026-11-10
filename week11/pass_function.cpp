#include <functional>

void func(int a) {
	return ;
}

template<typename Func>
void func_for_func(Func&& func) {
	func(30);
}

struct Lambda {
	int& a_;
	int operator()(int c) {
		return a_+c;
	}
};

int main() {
	int a;
	auto lambda = [&a](int c) -> int {
		return a + c;
	};
	Lambda lambda2(a);
	lambda2(30);
	func_for_func(lambda);
	return 0;
}
