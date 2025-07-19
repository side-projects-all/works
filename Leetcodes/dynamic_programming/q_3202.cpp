/*
You are given an integer array nums and a positive integer k.

A

sub of nums with length x is called valid if it satisfies:

    (sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k.

Return the length of the longest valid subsequence of nums.

 

Example 1:

Input: nums = [1,2,3,4,5], k = 2

Output: 5

Explanation:

The longest valid subsequence is [1, 2, 3, 4, 5].

Example 2:

Input: nums = [1,4,2,3,1,4], k = 3

Output: 4

Explanation:

The longest valid subsequence is [1, 4, 1, 4].

 

Constraints:

    2 <= nums.length <= 10^3
    1 <= nums[i] <= 10^7
    1 <= k <= 10^3

*/

class Solution {
private:
    int by_iterative_dp(vector<int>& nums, int& k) {
        int n = nums.size();
        if (n == 2) {
            return 2;
        }

        std::vector<std::vector<int>> dp(k, std::vector<int>(k));
        int max_len = 2;
        for (int n : nums) {
            n %= k;

            for (int prev = 0 ; prev < k; ++prev) {
                dp[prev][n] = dp[n][prev] + 1;
                max_len = std::max(max_len, dp[prev][n]);
            }
        }

        return max_len;
    }
public:
    int maximumLength(vector<int>& nums, int k) {
        return by_iterative_dp(nums, k);
    }
};