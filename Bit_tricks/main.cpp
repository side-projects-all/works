#include <iostream>
#include <numeric>
#include <fstream>
#include "All_tricks.h"
#include <algorithm>
#include <vector>
//#include "Solution.h"

class Solution {
private:
	bool is_less(char a, char b) {
		std::cout << "? " << a << " " << b << std::endl;
		char ans;
		std::cin >> ans;
		return ans == '<';
	}
public:
	Solution() {}
	~Solution() {}

	void q1() {
		
		int N = 0;
		int Q = 0;
		
		std::cin >> N >> Q;
		std::vector<char> sorted;
		sorted.push_back('A');

		for (int i = 1; i < N; ++i) {
			char curr = 'A' + i;
			int pos = sorted.size();

			for (int j = 0; j < sorted.size(); ++j) {
				if (is_less(curr, sorted[j])) {
					pos = j;
					break;
				}
			}

			sorted.insert(sorted.begin() + pos, curr);
		}

		std::cout << "! ";
		for (int i = 0; i < N; ++i) {
			std::cout << sorted[i];
		}
		std::cout << std::endl;
 	}
};


int main(int argc, char *argv[]) {
	Solution sol;
	sol.q1();

	/*
	All_tricks at;
	//at.Compute_the_sign_of_an_integer();
	//at.Compute_the_integer_absolute_value_without_branching();
	at.Detect_if_two_integers_have_opposite_signs();
	*/
	
	/*
	Solution sol;
	//std::vector<int> data{3, 1, 2};
	//std::vector<int> data(10000);
	//std::iota(data.begin(), data.end(), 10001);
	std::ofstream test_file("C:/Users/pj/Desktop/test1.txt");

	if (!test_file) {
        std::cerr << "Failed to open the file!\n";
        return 1;
    }
	
	test_file.close();

	std::vector<std::string> instructions = {"jump","add","add","jump","add","jump"};
	std::vector<int> values = {2,1,3,1,-2,-3};
	int ans = 0;
	//std::string ans;
	ans = sol.calculateScore(instructions, values);
	std::cout << ans << "\n";
	*/

	return 0;
}