/*
template <typename T>
T sum(const T& a, const T& b) {
	return a+b;
}
*/

#include <string>
double sum(double a, double b) {
	return a+b;
}

// overloading
std::string sum(const std::string& a, const std::string& b) {
	return a+b;
}
