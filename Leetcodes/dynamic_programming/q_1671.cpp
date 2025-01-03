/*
You may recall that an array arr is a mountain array if and only if:

    arr.length >= 3
    There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
        arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
        arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.

 

Example 1:

Input: nums = [1,3,1]
Output: 0
Explanation: The array itself is a mountain array so we do not need to remove any elements.

Example 2:

Input: nums = [2,1,1,5,6,2,3,1]
Output: 3
Explanation: One solution is to remove the elements at indices 0, 1, and 5, making the array nums = [1,5,6,3,1].

 

Constraints:

    3 <= nums.length <= 1000
    1 <= nums[i] <= 10^9
    It is guaranteed that you can make a mountain array out of nums.



*/

class Solution {
public:
    int minimumMountainRemovals(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> inc_max_left(n, 1);
        std::vector<int> dec_max_right(n, 1);

        //longest increasing subsequence from left
        for (int i = 0; i < n; ++i) {
            for (int j = i - 1; j >= 0; --j) {
                if (nums[i] > nums[j]) {
                    inc_max_left[i] = std::max(inc_max_left[i], inc_max_left[j] + 1);
                }
            }
        }

        //longest decreasing subsequence from right
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (nums[i] > nums[j]) {
                    dec_max_right[i] = std::max(dec_max_right[i], dec_max_right[j] + 1);
                }
            }
        }

        int min_remove = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (inc_max_left[i] > 1 && dec_max_right[i] > 1) {
                min_remove = std::min(min_remove, n - inc_max_left[i] - dec_max_right[i] + 1);
            }
        }

        return min_remove;
    }
};