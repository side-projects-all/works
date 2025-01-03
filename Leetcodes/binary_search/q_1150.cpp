/*
Given an integer array nums sorted in non-decreasing order and an integer target, return true if target is a majority element, or false otherwise.

A majority element in an array nums is an element that appears more than nums.length / 2 times in the array.

 

Example 1:

Input: nums = [2,4,5,5,5,5,5,6,6], target = 5
Output: true
Explanation: The value 5 appears 5 times and the length of the array is 9.
Thus, 5 is a majority element because 5 > 9/2 is true.

Example 2:

Input: nums = [10,100,101,101], target = 101
Output: false
Explanation: The value 101 appears 2 times and the length of the array is 4.
Thus, 101 is not a majority element because 2 > 4/2 is false.

 

Constraints:

    1 <= nums.length <= 1000
    1 <= nums[i], target <= 10^9
    nums is sorted in non-decreasing order.



*/

class Solution {
public:
    bool isMajorityElement(vector<int>& nums, int target) {
        //edge cases
        if (nums.size() == 1) {
            return nums[0] == target;
        }

        if (nums.size() == 2) {
            return nums[0] == target && nums[1] == target;
        }

        //doing binary seach two times to find target begin index and end index
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

        int begin = left;
        right = N - 1;
        int end = N;
        //do it again to find end index of target major
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > target) {
                right = mid - 1;
                end = mid;
                
            } else {
                left = mid + 1;
            }
        }

        return (end - begin) > (N / 2);
    }
};