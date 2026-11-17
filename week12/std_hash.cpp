#include <vector>
#include <cstdint>
#include <iostream>

struct MyType {
	int a;
	std::string b;
};

template<>
struct std::hash<MyType> {
	std::size_t operator()(const MyType& s) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(s.a);
        std::size_t h2 = std::hash<std::string>{}(s.b);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

int main() {
	auto hash_uint32_t = std::hash<uint32_t>{};
	auto hash_str = std::hash<std::string>{};
	std::cout << hash_uint32_t(345) << '\n';
	std::cout << hash_str("I am Sam") << '\n';
	return 0;
}
