/*
You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

    If x is a negative integer, then abs(x) = -x.
    If x is a non-negative integer, then abs(x) = x.

 

Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.

 

Constraints:

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4


*/

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();

        if (n == 1) {
            return std::abs(nums[0]);
        }

        int max_pos_sum = 0;
        int max_neg_sum = 0;
        int curr_pos_sum = 0;
        int curr_neg_sum = 0;

        for (int i = 0; i < n; ++i) {
            
            curr_pos_sum = std::max(0, curr_pos_sum) + nums[i];
            max_pos_sum = std::max(max_pos_sum, curr_pos_sum);

            curr_neg_sum = std::min(0, curr_neg_sum) + nums[i];
            max_neg_sum = std::min(max_neg_sum, curr_neg_sum);
        }

        return std::max(max_pos_sum, -max_neg_sum);
    }
};