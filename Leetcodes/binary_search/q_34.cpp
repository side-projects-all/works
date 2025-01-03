/*
Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]

Example 2:

Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]

Example 3:

Input: nums = [], target = 0
Output: [-1,-1]

 

Constraints:

    0 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9
    nums is a non-decreasing array.
    -10^9 <= target <= 10^9


*/

class Solution {

private:
    int binarySearch(vector<int>& nums, int target, bool findingBegin) {
        int N = nums.size();
        int left = 0;
        int right = N - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {

                if (findingBegin) {
                    if (mid == left || nums[mid - 1] < target) {
                        return mid;
                    }

                    right = mid - 1;
                } else {
                    if (mid == right || nums[mid + 1] > target) {
                        return mid;
                    }

                    left = mid + 1;
                }

            } else if (nums[mid] > target) {
                right = mid - 1;

            } else {
                left = mid + 1;
            }
        }

        return -1;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        //edge case: empty array
        if (nums.empty()) {
            return { -1, -1 };
        }
        //edge case: all values are the same as target
        if (nums[0] == target && nums[nums.size() - 1] == target) {
            return { 0, (int)(nums.size() - 1) };
        }

        int begin = binarySearch(nums, target, true);
        int end = binarySearch(nums, target, false);

        return { begin, end };
    }
};