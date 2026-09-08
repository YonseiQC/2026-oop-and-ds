#include <iostream>
#include <format>

void hanoi(int rod_from, int rod_to, int level) {
	if (level == 0) {
		return ;
	}
	int rod_intermediate = 6 - rod_from - rod_to;
	
	hanoi(rod_from, rod_intermediate, level-1);
	std::cout << std::format("Move a disk(size={}) from {} to {}\n", level, rod_from, rod_to);
	hanoi(rod_intermediate, rod_to, level-1);
}
int main() {
	hanoi(1, 3, 3);
	return 0;
}
