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
    int binary_search(vector<int>& nums, int target) {
        int n = nums.size();
        int b = 0;
        int e = n - 1;

        while (b < e) {
            int mid = b + (e - b) / 2;

            if (nums[mid] >= target) {
                e = mid;

            } else {
                
                b = mid + 1;
            }
        }

        return b;
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

        std::vector<int> ans(2, -1);
        int first = binary_search(nums, target);

        //not find first
        if (first == n || nums[first] != target) {
            return ans;
        }

        //find first, and try to find second
        int second = binary_search(nums, target + 1);
        if (second == n) {
            if (nums[n - 1] == target) {
                ans[0] = first;
                ans[1] = n - 1;

                return ans;

            } else {
                return ans;
            }
        }

        if (nums[second] == target) {
            ans[0] = first;
            ans[1] = second;
            return ans;
        }

        ans[0] = first;
        ans[1] = second - 1;
        return ans;
    }
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return by_binary_search(nums, target);
    }
};