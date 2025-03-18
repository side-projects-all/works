/*
Given an integer n represented as a string, return the smallest good base of n.

We call k >= 2 a good base of n, if all digits of n base k are 1's.

 

Example 1:

Input: n = "13"
Output: "3"
Explanation: 13 base 3 is 111.

Example 2:

Input: n = "4681"
Output: "8"
Explanation: 4681 base 8 is 11111.

Example 3:

Input: n = "1000000000000000000"
Output: "999999999999999999"
Explanation: 1000000000000000000 base 999999999999999999 is 11.

 

Constraints:

    n is an integer in the range [3, 10^18].
    n does not contain any leading zeros.


*/

class Solution {
private:
    std::string by_binary_search(string& n) {
        unsigned long long num = std::stoll(n);

        for (int m = (int)std::log2(num); m >= 1; --m) {

            if ((1ULL << m) > num) {
                continue;
            }

            unsigned long long left = 2;
            unsigned long long right = std::pow(num, 1.0 / m) + 1;

            while (left <= right) {
                unsigned long long mid = left + (right - left) / 2;

                unsigned long long sum = 1;
                unsigned long long val = mid;

                for (int i = 1; i <= m; ++i) {
                    sum += val;
                    val *= mid;
                }

                if (sum == num) {
                    return std::to_string(mid);

                } else if (sum > num) {
                    right = mid - 1;

                } else {
                    left = mid + 1;
                }
            }
        }

        return std::to_string(num - 1);
    }
    std::string old_way(string& n) {
        long long num = std::stoll(n); 

        //try from the largest possible value of m and decrement
        for (int m = std::log2(num) + 1; m >= 2; --m) {

            //possible base k
            long long k = std::pow(num, 1.0 / (m - 1));  

            // Check if the current k is the correct base
            long long sum = 1;
            long long curr = 1;
            for (int i = 1; i < m; ++i) {
                curr *= k;
                sum += curr;
            }

            if (sum == num) {
                return std::to_string(k);  //return the base as a string
            }
        }

        //no other base is found, the smallest good base is `n-1`
        return std::to_string(num - 1);
    }
public:
    string smallestGoodBase(string n) {
        //return old_way(n);
        return by_binary_search(n);
    }
};