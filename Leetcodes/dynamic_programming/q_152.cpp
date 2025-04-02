/*
Given an integer array nums, find a
subarray
that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

 

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.

 

Constraints:

    1 <= nums.length <= 2 * 10^4
    -10 <= nums[i] <= 10
    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.


*/

class Solution {
private:
    int by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }
        int max_prod = nums[0];
        int curr_min_prod = nums[0];
        int curr_max_prod = nums[0];
        for (int i = 1; i < n; ++i) {

            int curr_max = std::max(nums[i], std::max(curr_max_prod * nums[i], curr_min_prod * nums[i]));
            curr_min_prod = std::min(nums[i], std::min(curr_max_prod * nums[i], curr_min_prod * nums[i]));

            curr_max_prod = curr_max;
            max_prod = std::max(max_prod, curr_max_prod);
        }

        return max_prod;
    }
public:
    int maxProduct(vector<int>& nums) {
        return by_iterative_dp(nums);
    }
};