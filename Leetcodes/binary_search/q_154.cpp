/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times. For example, the array nums = [0,1,4,4,5,6,7] might become:

    [4,5,6,7,0,1,4] if it was rotated 4 times.
    [0,1,4,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.

You must decrease the overall operation steps as much as possible.

 

Example 1:

Input: nums = [1,3,5]
Output: 1

Example 2:

Input: nums = [2,2,2,0,1]
Output: 0

 

Constraints:

    n == nums.length
    1 <= n <= 5000
    -5000 <= nums[i] <= 5000
    nums is sorted and rotated between 1 and n times.

*/

class Solution {
private:
    int by_binary_search(vector<int>& nums) {
        class Solution {
private:
    int by_binary_search(vector<int>& nums) {
        int n = nums.size();
        if (n == 1 || nums[0] < nums[n - 1]) {
            return nums[0];
        }

        int b = 0;
        int e = n - 1;
        while (b < e) {
            while (b < e && nums[b] == nums[b + 1]) {
                ++b;
            }

            while (b < e && nums[e] == nums[e - 1]) {
                --e;
            }

            int mid = b + (e - b) / 2;

            if (mid - 1 >= 0 && nums[mid] < nums[mid - 1]) {
                return nums[mid];
            }

            if (mid + 1 < n && nums[mid] > nums[mid + 1]) {
                return nums[mid + 1];
            }

            //different from leetcode 153, because of duplicates, ex: [0,0,1,1,2,0]
            if (nums[mid] >= nums[b]) {
                b = mid + 1;
                
            } else {
                e = mid;
            }
        }

        return b == n ? nums[b - 1] : nums[b];
    }
public:
    int findMin(vector<int>& nums) {
        return by_binary_search(nums);
    }
};
    }
public:
    int findMin(vector<int>& nums) {
        return by_binary_search(nums);
    }
};