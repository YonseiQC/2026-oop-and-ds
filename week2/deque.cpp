#include <deque>
#include <string>

int main() {
	std::deque<std::string> v;
	v.push_front("Hello, ");
	v.push_back("world!");
	return 0;
}
