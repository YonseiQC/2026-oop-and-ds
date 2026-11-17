#include <iostream>
#include <cstdint>
#include <bitset>

void print_to_bin(double val) {
	uint64_t *p = (uint64_t*)&val;
	std::cout << val << ": " << std::bitset<64>(*p) << '\n';
}

void print_to_hex(double val) {
	unsigned char *p = (unsigned char*)&val;
	printf("%02X %02X %02X %02X %02X %02X %02X %02X\n", p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
}
int main() {
	print_to_bin(1.0);
	print_to_hex(1.0);
	print_to_bin(2.0);
	print_to_bin(0.5);
	print_to_bin(0.1);
	return 0;
}
