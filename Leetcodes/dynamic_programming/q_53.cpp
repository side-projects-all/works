/*
Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

A subarray is a contiguous part of an array.

Ex 1:
Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.

Ex 2:
Input: nums = [1]
Output: 1

Ex 3:
Input: nums = [5,4,-1,7,8]
Output: 23

Constraints:

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int max_sum = INT_MIN;
        int curr_sum = 0;

        for (int i = 0; i < nums.size(); ++i) {
            curr_sum = std::max(curr_sum, 0) + nums[i];
            max_sum = std::max(max_sum, curr_sum);
        }
        return max_sum;
        
        /*
        std::vector<int> dp(nums.size());

        dp[0] = nums[0];
        int max_sub = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            dp[i] = std::max(nums[i], dp[i - 1] + nums[i]);
            max_sub = std::max(max_sub, dp[i]);
        }

        return max_sub;
        */
    }
};