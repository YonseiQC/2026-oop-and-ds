#include <concepts>

template <std::integral T>
T greatest_common_divisor(T a, T b) {
    while (b != 0) {
        T remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
