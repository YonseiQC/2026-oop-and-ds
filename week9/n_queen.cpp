#include <cmath>
#include <vector>
#include <iostream>

class NQueenSolver {
private:
	int n_;
	std::vector<int> cols_;
	int num_sol_ = 0;

	void solve(int row) {
		const int n = n_;
		if ( row == n) {
			++num_sol_;
			return ;
		}
		for(int col = 0; col < n; col++) {
			bool this_col_avail = true;
			for(int i = 0; i < row; i++) {
				if(cols_[i] == col || abs(row-i) == abs(cols_[i] - col)) {
					this_col_avail = false;
					break;
				}
			}
			if (this_col_avail) {
				cols_[row] = col;
				solve(row+1);
			}
		}
	}
public:
	explicit NQueenSolver(int n) : n_(n), cols_(n, -1) {
		solve(0);
	}


	int num_sol() {
		return num_sol_;
	}
};

int main() {
	int n;
	std::cin >> n;
	NQueenSolver solver(n);
	std::cout << solver.num_sol() << '\n';
	return 0;
}
