/*
Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num.

 

Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.

Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.

Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

 

Constraints:

    1 <= k <= num.length <= 10^5
    num consists of only digits.
    num does not have any leading zeros except for the zero itself.


*/

class Solution {
public:
    string removeKdigits(string num, int k) {
        if (k == num.size()) {
            return "0";
        }

        std::string ans;

        for (char c : num) {
            while (ans.size() > 0 && k > 0 && ans.back() > c) {
                ans.pop_back();
                --k;
            }

            ans.push_back(c);
        }

        for (int i = 0; i < k; ++i) {
            ans.pop_back();
        }

        int first_not_zero = -1;
        for (int i = 0; i < ans.size(); ++i) {

            if (ans[i] != '0') {
                first_not_zero = i;
                break;
            }
        }

        return first_not_zero != -1 ? ans.substr(first_not_zero) : "0";
    }
};