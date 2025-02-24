/*
Given an array nums of integers and integer k, return the maximum sum such that there exists i < j with nums[i] + nums[j] = sum and sum < k. If no i, j exist satisfying this equation, return -1.

 

Example 1:

Input: nums = [34,23,1,24,75,33,54,8], k = 60
Output: 58
Explanation: We can use 34 and 24 to sum 58 which is less than 60.

Example 2:

Input: nums = [10,20,30], k = 15
Output: -1
Explanation: In this case it is not possible to get a pair sum less that 15.

 

Constraints:

    1 <= nums.length <= 100
    1 <= nums[i] <= 1000
    1 <= k <= 2000


*/

class Solution {
private:
    int by_two_ptr(vector<int>& nums, int& k) {
        int n = nums.size();
        int ans = -1;
        int left = 0;
        int right = n - 1;
        while (left < right) {

            if (nums[left] + nums[right] < k) {
                ans = std::max(ans, nums[left] + nums[right]);
                ++left;
                
            } else {
                --right;
            }
        }

        return ans;
    }
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());

        if (nums.size() < 2) {
            return -1;
        }

        return by_two_ptr(nums, k);
    }
};