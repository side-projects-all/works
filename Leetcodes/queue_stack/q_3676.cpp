/*
You are given an integer array nums with distinct elements.

A

nums[l...r] of nums is called a bowl if:

    The subarray has length at least 3. That is, r - l + 1 >= 3.
    The minimum of its two ends is strictly greater than the maximum of all elements in between. That is, min(nums[l], nums[r]) > max(nums[l + 1], ..., nums[r - 1]).

Return the number of bowl subarrays in nums.

 

Example 1:

Input: nums = [2,5,3,1,4]

Output: 2

Explanation:

The bowl subarrays are [3, 1, 4] and [5, 3, 1, 4].

    [3, 1, 4] is a bowl because min(3, 4) = 3 > max(1) = 1.
    [5, 3, 1, 4] is a bowl because min(5, 4) = 4 > max(3, 1) = 3.

Example 2:

Input: nums = [5,1,2,3,4]

Output: 3

Explanation:

The bowl subarrays are [5, 1, 2], [5, 1, 2, 3] and [5, 1, 2, 3, 4].

Example 3:

Input: nums = [1000000000,999999999,999999998]

Output: 0

Explanation:

No subarray is a bowl.

 

Constraints:

    3 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    nums consists of distinct elements.

*/

class Solution {
public:
    long long bowlSubarrays(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> left(n, -1);
        std::vector<int> right(n, n);
        std::vector<int> stack;

        //right bound
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[i] >= nums[stack.back()]) {
                stack.pop_back();
            }
            right[i] = stack.empty() ? n : stack.back();
            stack.push_back(i);
        }
        
        //left bound
        stack.clear();
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[i] >= nums[stack.back()]) {
                
                stack.pop_back();
            }
            left[i] = stack.empty() ? -1 : stack.back();
            stack.push_back(i);
        }

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            if (right[i] != n && left[i] != -1 && right[i] - left[i] + 1 >= 3) {
                ++ans;
            }
        }

        return ans;
    }
};