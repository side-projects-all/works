/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.

 

Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]

 

Constraints:

    2 <= nums.length <= 10^5
    -30 <= nums[i] <= 30
    The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        std::vector<int> ans(nums.size());

        ans[0] = 1;
        for (int i = 1; i < nums.size(); ++i) {
            ans[i] = ans[i - 1] * nums[i - 1];
        }

        int r = 1;
        for (int i = nums.size() - 1; i >= 0 ; --i) {
            ans[i] = ans[i] * r;
            r *= nums[i];
        }

        return ans;
        /*
        int N = nums.size();
        std::vector<int> L(N, 0);
        std::vector<int> R(N, 0);
        L[0] = 1;
        R[N - 1] = 1;
        for (int left = 1, right = N - left - 1; left < N; ++left, --right) {
            
            L[left] = L[left - 1] * nums[left - 1];
            R[right] = R[right + 1] * nums[right + 1];
        }

        std::vector<int> ans(N, 0);
        for (int i = 0; i < N; ++i) {
            ans[i] = L[i] * R[i];
        }

        return ans;
        */
    }
};