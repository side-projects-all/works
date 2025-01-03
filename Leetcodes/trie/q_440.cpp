/*
Given two integers n and k, return the kth lexicographically smallest integer in the range [1, n].

 

Example 1:

Input: n = 13, k = 2
Output: 10
Explanation: The lexicographical order is [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], so the second smallest number is 10.

Example 2:

Input: n = 1, k = 1
Output: 1

 

Constraints:

    1 <= k <= n <= 10^9


*/

class Solution {
public:
    int findKthNumber(int n, int k) {
        int curr = 1;
        --k;    //1 is already counted

        while (k > 0) {
            int steps = cnt_steps(n, curr, curr + 1);

            if (steps <= k) {
                ++curr;
                k -= steps;

            } else {
                curr *= 10;
                --k;
            }
        }

        return curr;
    }
private:
    int cnt_steps(long n, long pre1, long pre2) {
        int steps = 0;

        while (pre1 <= n) {
            steps += std::min(n + 1, pre2) - pre1;
            pre1 *= 10;
            pre2 *= 10;
        }

        return steps;
    }
};