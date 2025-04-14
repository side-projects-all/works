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
private:
    int by_sliding_window(vector<int>& nums) {
        int n = nums.size();
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
    }
    int by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        //std::vector<int> dp(n);
        int cnt = 0;
        int len = 0;
        for (int i = 2; i < n; ++i) {

            if (nums[i - 1] - nums[i - 2] == nums[i] - nums[i - 1]) {
                //dp[i] = 1 + dp[i - 1];
                ++len;
                cnt += len;
                //cnt += dp[i];
            } else {
                len = 0;
            }
        }

        return cnt;
    }
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        //return by_iterative_dp(nums);
        return by_sliding_window(nums);
    }
};