#include <iostream>
#include <numeric>
#include <fstream>
#include "All_tricks.h"
#include "Solution.h"

int main(int argc, char *argv[]) {

	/*
	All_tricks at;
	//at.Compute_the_sign_of_an_integer();
	//at.Compute_the_integer_absolute_value_without_branching();
	at.Detect_if_two_integers_have_opposite_signs();
	*/
	
	/**/
	Solution sol;
	//std::vector<int> data{3, 1, 2};
	//std::vector<int> data(10000);
	//std::iota(data.begin(), data.end(), 10001);
	std::ofstream test_file("C:/Users/pj/Desktop/test1.txt");

	if (!test_file) {
        std::cerr << "Failed to open the file!\n";
        return 1;
    }
	std::string str = "bacabbacab";
	std::string final;
	for (int i = 0; i < 499; ++i) {
		final += str;
	}
	std::string rev = final;
	std::reverse(final.begin(), final.end());
	final = final + "z" + rev;

	test_file << final;
	test_file.close();
	std::cout << "len: " << final.size() << "\n";
	std::string str2 = "bacabbacab";
	//int ans = 0;
	std::string ans;
	ans = sol.smallestPalindrome(str2, 5);
	std::cout << ans << "\n";
	

	return 0;
}