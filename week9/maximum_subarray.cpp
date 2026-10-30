#include <tuple>
#include <limits>
#include <vector>
#include <format>
#include <iostream>

auto find_maximum_crossing_subarray(int* arr, int low, int mid, int high)
-> std::tuple<int, int, int> {
	int left_sum = std::numeric_limits<int>::min();
	int sum = 0;
	int max_left = mid;

	for(int i = mid; i >= low; --i) {
		sum = sum + arr[i];
		if (sum > left_sum) {
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = 0;
	int max_right = mid+1;
	sum = 0;
	for(int j = mid+1; j < high; j++) {
		sum = sum + arr[j];
		if(sum > right_sum) {
			right_sum = sum;
			max_right = j;
		}
	}
	return std::make_tuple(max_left, max_right, left_sum + right_sum);
}

std::tuple<int, int, int> find_maximum_subarray(int* arr, int low, int high) {
	if(high - low <= 1) {
		return std::make_tuple(low, high, arr[low]);
	}
	int mid = (low+high)/2;
	const auto [left_low, left_high, left_sum] 
		= find_maximum_subarray(arr, low, mid);
	const auto [right_low, right_high, right_sum] 
		= find_maximum_subarray(arr, mid, high);
	const auto [cross_low, cross_high, cross_sum]
		= find_maximum_crossing_subarray(arr, low, mid, high);

	if(left_sum > right_sum && left_sum > cross_sum) {
		return std::make_tuple(left_low, left_high, left_sum);
	}
	if(right_sum > left_sum && right_sum > cross_sum) {
		return std::make_tuple(right_low, right_high, right_sum);
	}
	return std::make_tuple(cross_low, cross_high, cross_sum);
}

int main() {
	std::vector<int> arr{13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	const auto [low, high, sum] = find_maximum_subarray(arr.data(), 0, arr.size());

	std::cout << std::format("low: {}\n", low);
	std::cout << std::format("high: {}\n", high);
	std::cout << std::format("sum: {}\n", sum);
	return 0;
}
