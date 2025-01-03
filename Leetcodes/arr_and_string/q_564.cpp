/*
Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.

The closest is defined as the absolute difference minimized between two integers.

 

Example 1:

Input: n = "123"
Output: "121"

Example 2:

Input: n = "1"
Output: "0"
Explanation: 0 and 2 are the closest palindromes but we return the smallest which is 0.

 

Constraints:

    1 <= n.length <= 18
    n consists of only digits.
    n does not have leading zeros.
    n is representing an integer in the range [1, 10^18 - 1].


*/

class Solution {
public:
    string nearestPalindromic(string n) {
        int len = n.size();
        bool is_even = false;
        int i = 0;

        if (len % 2 == 0) {
            i = len / 2 - 1;
            is_even = true;
        } else {
            i = len / 2;
        }
        long first_half = std::stol(n.substr(0, i + 1));

        std::vector<long> possibilities;
        possibilities.push_back(half_changed(first_half, is_even));
        possibilities.push_back(half_changed(first_half + 1, is_even));
        possibilities.push_back(half_changed(first_half - 1, is_even));
        possibilities.push_back((long)std::pow(10, len - 1) - 1);
        possibilities.push_back((long)std::pow(10, len) + 1);

        long diff = LONG_MAX;
        long ans = 0;
        long n_to_l = std::stol(n);

        for (auto candidate : possibilities) {
            if (candidate == n_to_l) {
                continue;
            }

            if (std::abs(candidate - n_to_l) < diff) {
                diff = std::abs(candidate - n_to_l);
                ans = candidate;
            } else if (std::abs(candidate - n_to_l) == diff) {
                ans = std::min(ans, candidate);
            }
        }

        return std::to_string(ans);
    }
private:
    long half_changed(long left, bool is_even) {
        long ans = left;

        if (!is_even) {
            left /= 10;
        }

        while (left > 0) {
            ans = ans * 10 + left % 10;
            left /= 10;
        }

        return ans;
    }
};