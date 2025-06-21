#include <iostream>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <vector>
#include "All_tricks.h"
#include "Solution.h"


int main(int argc, char *argv[]) {

	//All_tricks all;
	//all.invert_endian();
	Solution sol;
	long long val = sol.countGoodArrays(5, 10, 2);
	std::cout << val << "\n";
	return 0;
}