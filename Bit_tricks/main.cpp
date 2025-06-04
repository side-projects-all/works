#include <iostream>
#include <numeric>
#include <fstream>
#include <algorithm>
#include <vector>


int main(int argc, char *argv[]) {

	int w = 0;
	std::cin >> w;

	int first = w / 2;
	int sec = w - first;
	
	while (first > 0 && sec > 0 ) {

		if (first % 2 == 0 && sec % 2 == 0) {
			std::cout << "YES";
			return 0;
		}

		++first;
		--sec;
	}

	std::cout << "NO";

	return 0;
}