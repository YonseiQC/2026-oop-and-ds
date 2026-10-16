#include "string_sum.hpp"
#include <iostream>

std::string odyssey() {
    return sum("Odysseus ", "is back!");
}

int main() {
    std::string d = odyssey();
    std::cout << d << '\n';
    return 0;
}