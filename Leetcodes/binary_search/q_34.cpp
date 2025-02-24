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
    int bs_upper(vector<int>& nums, int left, int right, int& target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {

                if (mid == right || nums[mid + 1] != target) {
                    return mid;
                }

                left = mid + 1;

            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return -1;
    }
    int bs_lower(vector<int>& nums, int left, int right, int& target) {
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                if (mid == left || nums[mid - 1] != target) {
                    return mid;
                }

                right = mid - 1;
            } else if (nums[mid] > target) {
                right = mid - 1;

            } else {
                left = mid + 1;
            }
        }

        return -1;
    }
    std::vector<int> by_binary_search(vector<int>& nums, int& target) {
        int n = nums.size();
        if (n == 0) {
            return {-1, -1};
        }

        if (n == 1) {
            if (nums[0] == target) {
                return {0, 0};
            } else {
                return {-1, -1};
            }
        }

        if (target < nums[0] || target > nums[n - 1]) {
            return {-1, -1};
        }

        std::vector<int> ans(2, -1);
        ans[0] = bs_lower(nums, 0, n - 1, target);

        if (ans[0] == -1) {
            return ans;
        }

        ans[1] = bs_upper(nums, ans[0], n - 1, target);

        return ans;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return by_binary_search(nums, target);
    }
};