/*
Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.

 

Example 1:

Input: nums = [1,3,5,4,7]
Output: 2
Explanation: The two longest increasing subsequences are [1, 3, 4, 7] and [1, 3, 5, 7].

Example 2:

Input: nums = [2,2,2,2,2]
Output: 5
Explanation: The length of the longest increasing subsequence is 1, and there are 5 increasing subsequences of length 1, so output 5.

 

Constraints:

    1 <= nums.length <= 2000
    -10^6 <= nums[i] <= 10^6


*/

class Solution {
private:
    void recursive(vector<int>& nums, std::vector<int>& dp, std::vector<int>& cnt, int i) {
        if (dp[i] != 0) {
            return;
        }

        dp[i] = 1;
        cnt[i] = 1;

        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {

                //go deeper
                recursive(nums, dp, cnt, j);

                if (dp[i] < dp[j] + 1) {
                    dp[i] = dp[j] + 1;
                    cnt[i] = 0;
                }

                if (dp[i] == dp[j] + 1) {
                    cnt[i] += cnt[j];
                }
            }
        }
    }
    int by_recursive_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp(n, 0);
        std::vector<int> cnt(n, 0);

        int max_len = 0;
        for (int i = 0; i < n; ++i) {
            recursive(nums, dp, cnt, i);

            if (dp[i] > max_len) {
                max_len = dp[i];
            }
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (dp[i] == max_len) {
                ans += cnt[i];
            }
        }

        return ans;
    }
    int by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp(n, 1);
        std::vector<int> cnt(n, 1);
        int max_len = 0;

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {

                if (nums[i] > nums[j]) {

                    if (dp[i] < dp[j] + 1) {
                        dp[i] = dp[j] + 1;
                        cnt[i] = 0;
                    }
                    
                    if (dp[i] == dp[j] + 1) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            max_len = std::max(max_len, dp[i]);
        }

        int ans = 0;

        for (int i = 0; i < n; ++i) {
            if (dp[i] == max_len) {
                ans += cnt[i];
            }
        }

        return ans;
    }
public:
    int findNumberOfLIS(vector<int>& nums) {
        return by_iterative_dp(nums);
        //return by_recursive_dp(nums);
    }
};