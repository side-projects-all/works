/*
A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The width of such a ramp is j - i.

Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.

 

Example 1:

Input: nums = [6,0,8,2,1,5]
Output: 4
Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.

Example 2:

Input: nums = [9,8,1,0,1,9,4,0,4,1]
Output: 7
Explanation: The maximum width ramp is achieved at (i, j) = (2, 9): nums[2] = 1 and nums[9] = 1.

 

Constraints:

    2 <= nums.length <= 5 * 10^4
    0 <= nums[i] <= 5 * 10^4


*/

class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        return two_ptr(nums);
    }

private:
    int two_ptr(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> right_max(n);

        right_max[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            right_max[i] = std::max(right_max[i + 1], nums[i]);
        }
        int b = 0;
        int e = 0;
        int max_len = 0;
        while (e < n) {
            while (b < e && nums[b] > right_max[e]) {
                ++b;
            }

            max_len = std::max(max_len, e - b);
            ++e;
        }
        
        return max_len;
    }
};