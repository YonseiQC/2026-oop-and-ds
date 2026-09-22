#include <cstdint>
#include <string>

class Student {
public:
	uint32_t id_;
	std::string name_;

	uint32_t get_id() const {
		return id_;
	}

	std::string get_name() const {
		return name_;
	}
};

int main() {
	Student student(42244, std::string("Chae-Yeun Park"));
	return 0;
}
