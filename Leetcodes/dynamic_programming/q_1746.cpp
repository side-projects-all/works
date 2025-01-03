/*
You are given an integer array nums. You must perform exactly one operation where you can replace one element nums[i] with nums[i] * nums[i]. 

Return the maximum possible subarray sum after exactly one operation. The subarray must be non-empty.

 

Example 1:

Input: nums = [2,-1,-4,-3]
Output: 17
Explanation: You can perform the operation on index 2 (0-indexed) to make nums = [2,-1,16,-3]. Now, the maximum subarray sum is 2 + -1 + 16 = 17.

Example 2:

Input: nums = [1,-1,1,1,-1,-1,1]
Output: 4
Explanation: You can perform the operation on index 1 (0-indexed) to make nums = [1,1,1,1,-1,-1,1]. Now, the maximum subarray sum is 1 + 1 + 1 + 1 = 4.

 

Constraints:

    1 <= nums.length <= 10^5
    -10^4 <= nums[i] <= 10^4

*/

class Solution {
public:
    int maxSumAfterOperation(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> max_left(n);
        std::vector<int> max_right(n);

        //max_left[0] = 0;
        for (int i = 1; i < n; ++i) {
            max_left[i] = std::max(max_left[i - 1] + nums[i - 1], 0);
        }

        max_right[n - 1] = 0;
        for (int i = n - 2; i >= 0; --i) {
            max_right[i] = std::max(max_right[i + 1] + nums[i + 1], 0);
        }

        int max_sum = 0;
        for (int i = 0; i < n; ++i) {
            max_sum = std::max(max_sum, max_left[i] + nums[i] * nums[i] + max_right[i]);
        }

        return max_sum;
    }
};