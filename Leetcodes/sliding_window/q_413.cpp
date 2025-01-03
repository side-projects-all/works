/*
An integer array is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

    For example, [1,3,5,7,9], [7,7,7,7], and [3,-1,-5,-9] are arithmetic sequences.

Given an integer array nums, return the number of arithmetic subarrays of nums.

A subarray is a contiguous subsequence of the array.

 

Example 1:

Input: nums = [1,2,3,4]
Output: 3
Explanation: We have 3 arithmetic slices in nums: [1, 2, 3], [2, 3, 4] and [1,2,3,4] itself.

Example 2:

Input: nums = [1]
Output: 0

 

Constraints:

    1 <= nums.length <= 5000
    -1000 <= nums[i] <= 1000


*/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        //return naive(nums, n);
        //return dp(nums, n);
        return sliding_window(nums, n);
    }

private:
    int sliding_window(vector<int>& nums, int& n) {

        if (n < 3) return 0; // Minimum 3 elements are needed for an arithmetic slice

        int start = 0, totalSlices = 0;

        for (int end = 2; end < n; ++end) {
            // Check if nums[start:end] has a constant difference
            if (nums[end] - nums[end - 1] == nums[end - 1] - nums[end - 2]) {
                // If we have an arithmetic sequence up to `end`, add the number of slices
                totalSlices += end - start - 1;
            } else {
                // Reset start to end - 1 to start a new arithmetic sequence
                start = end - 1;
            }
        }

        return totalSlices;

        //do not remember why using freq??
        /*
        int s = 0;
        int e = 1;
        int prev_diff = nums[e] - nums[s];
        ++e;
        int cnt = 0;
        int freq = 0;
        int len = 2;

        while (e < n) {
            if (nums[e] - nums[e - 1] == prev_diff) {
                ++e;
                ++len;

                if (len == 3) {
                    cnt += 1;
                    freq = 2;
                }

                if (len > 3) {
                    cnt += freq;
                    ++freq;
                }
            } else {
                s = e - 1;
                prev_diff = nums[e] - nums[s];
                len = 2;
                ++e;
            }
        }

        return cnt;
        */
    }
    int dp(vector<int>& nums, int& n) {
        int cnt = 0;
        //std::vector<int> dp(n);
        int dp = 0;

        for (int i = 2; i < n; ++i) {
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                dp = 1 + dp;
                cnt += dp;
            } else {
                dp = 0;
            }
            /*
            if (nums[i] - nums[i - 1] == nums[i - 1] - nums[i - 2]) {
                dp[i] = 1 + dp[i - 1];
                cnt += dp[i];
            }
            */
        }

        return cnt;
    }
    int naive(vector<int>& nums, int& n) {
        int cnt = 0;
        for (int len = 3; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {

                int diff =  nums[i + 1] - nums[i];
                bool same_diff = true;
                for (int j = i + 2; j < i + len; ++j) {
                    if (nums[j] - nums[j - 1] != diff) {
                        same_diff = false;
                        break;
                    }
                }

                if (same_diff) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }
};