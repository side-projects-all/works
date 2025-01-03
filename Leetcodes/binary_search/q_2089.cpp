/*
You are given a 0-indexed integer array nums and a target element target.

A target index is an index i such that nums[i] == target.

Return a list of the target indices of nums after sorting nums in non-decreasing order. If there are no target indices, return an empty list. The returned list must be sorted in increasing order.

 

Example 1:

Input: nums = [1,2,5,2,3], target = 2
Output: [1,2]
Explanation: After sorting, nums is [1,2,2,3,5].
The indices where nums[i] == 2 are 1 and 2.

Example 2:

Input: nums = [1,2,5,2,3], target = 3
Output: [3]
Explanation: After sorting, nums is [1,2,2,3,5].
The index where nums[i] == 3 is 3.

Example 3:

Input: nums = [1,2,5,2,3], target = 5
Output: [4]
Explanation: After sorting, nums is [1,2,2,3,5].
The index where nums[i] == 5 is 4.

 

Constraints:

    1 <= nums.length <= 100
    1 <= nums[i], target <= 100


*/

class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        std::sort(nums.begin(), nums.end());

        std::vector<int> result;
        int N = nums.size();
        int left = 0;
        int right = N - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        int left_bound = left;

        //for empty case
        if (left >= N || nums[left] != target) {
            return result;
        }
        result.push_back(left);
        
        //start from left to search
        right = N - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        left = (nums[left] == target) ? left : left - 1;
        for (int i = left_bound + 1; i <= left; ++i) {
            result.push_back(i);
        }

        return result;
    }
};