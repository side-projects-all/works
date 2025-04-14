/*
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:

    answer[i] % answer[j] == 0, or
    answer[j] % answer[i] == 0

If there are multiple solutions, return any of them.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.

Example 2:

Input: nums = [1,2,4,8]
Output: [1,2,4,8]

 

Constraints:

    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 10^9
    All the integers in nums are unique.


*/

class Solution {
private:
    vector<int> by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return {nums[0]};
        }

        std::sort(nums.begin(), nums.end());
        std::vector<int> dp(n, 1);      //max length
        int max_len = 1;

        for (int e = 1; e < n; ++e) {

            for (int b = 0; b < e; ++b) {
                if (nums[e] % nums[b] == 0 && dp[e] < dp[b] + 1) {
                    dp[e] = dp[b] + 1;
                    max_len = std::max(max_len, dp[e]);
                }
            }
        }

        std::vector<int> ans(max_len);
        int max_num = -1;
        for (int i = n - 1; i >= 0; --i) {
            if (max_len == dp[i] && (max_num == -1 || max_num % nums[i] == 0)) {
                ans[max_len - 1] = nums[i];
                max_num = nums[i];
                --max_len;
            }
        }

        return ans;
    }
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        return by_iterative_dp(nums);
    }
};