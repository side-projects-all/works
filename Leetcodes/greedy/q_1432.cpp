/*
You are given an integer num. You will apply the following steps to num two separate times:

    Pick a digit x (0 <= x <= 9).
    Pick another digit y (0 <= y <= 9). Note y can be equal to x.
    Replace all the occurrences of x in the decimal representation of num by y.

Let a and b be the two results from applying the operation to num independently.

Return the max difference between a and b.

Note that neither a nor b may have any leading zeros, and must not be 0.

 

Example 1:

Input: num = 555
Output: 888
Explanation: The first time pick x = 5 and y = 9 and store the new integer in a.
The second time pick x = 5 and y = 1 and store the new integer in b.
We have now a = 999 and b = 111 and max difference = 888

Example 2:

Input: num = 9
Output: 8
Explanation: The first time pick x = 9 and y = 9 and store the new integer in a.
The second time pick x = 9 and y = 1 and store the new integer in b.
We have now a = 9 and b = 1 and max difference = 8

 

Constraints:

    1 <= num <= 10^8


*/

class Solution {
private:
    
public:
    int maxDiff(int num) {
        if (num < 10) {
            return 8;
        }

        std::string max_digits = std::to_string(num);
        std::string min_digits = max_digits;
        int n = max_digits.size();

        //max, from left, find first not equal to 9
        for (int i = 0; i < n; ++i) {
            if (max_digits[i] != '9') {

                char d = max_digits[i];
                for (int j = i; j < n; ++j) {
                    if (max_digits[j] == d) {
                        max_digits[j] = '9';
                    }
                }

                break;
            }
        }

        //min from left, find first not equal to 1
        for (int i = 0; i < n; ++i) {

            if (i == 0) {
                if (min_digits[i] != '1') {

                    char d = min_digits[i];
                    for (int j = i; j < n; ++j) {
                        if (min_digits[j] == d) {
                            min_digits[j] = '1';
                        }
                    }

                    break;
                }

            } else {
                if (min_digits[i] != '0' && min_digits[i] != min_digits[0]) {

                    char d = min_digits[i];
                    for (int j = i; j < n; ++j) {
                        if (min_digits[j] == d) {
                            min_digits[j] = '0';
                        }
                    }

                    break;
                }
            }
        }

        return stoi(max_digits) - stoi(min_digits);
    }
};