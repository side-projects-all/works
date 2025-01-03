/*
Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.

 

Example 1:

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Explanation: After squaring, the array becomes [16,1,0,9,100].
After sorting, it becomes [0,1,9,16,100].

Example 2:

Input: nums = [-7,-3,2,3,11]
Output: [4,9,9,49,121]

 

Constraints:

    1 <= nums.length <= 10^4
    -10^4 <= nums[i] <= 10^4
    nums is sorted in non-decreasing order.

*/

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {

        //using two pointer !!
        int len = nums.size();

        std::vector<int> sq(len, 0);
        int left = 0;
        int right = len - 1;

        for (int i = len - 1; i > -1; --i) {
            int curr = 0;
            if (std::abs(nums[left]) < std::abs(nums[right])) {
                curr = nums[right];
                --right;
            } else {
                curr = nums[left];
                ++left;
            }

            sq[i] = curr * curr;
        }

    
        return sq;
    }
};