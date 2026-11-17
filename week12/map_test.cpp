#include <map>
#include <string>

struct NonComparable {
	int a;
	std::string b;
};

bool operator<(const NonComparable& lhs, const NonComparable& rhs) {
	return (lhs.a < rhs.a) && (lhs.b < rhs.b);
}

int main() {
	std::map<NonComparable, int> m;

	m[NonComparable(3, "abc")] = 19;
	return 0;
}
