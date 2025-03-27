#include <iostream>
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
	std::vector<int> nums{-3,-2,-1,0,0,1,2};
	long long ans = sol.maximumCount(nums);
	std::cout << ans << "\n";

	return 0;
}