/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly rotated at an unknown pivot index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

 

Example 1:

Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:

Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:

Input: nums = [1], target = 0
Output: -1

 

Constraints:

    1 <= nums.length <= 5000
    -10^4 <= nums[i] <= 10^4
    All values of nums are unique.
    nums is an ascending array that is possibly rotated.
    -10^4 <= target <= 10^4


*/

class Solution {
private:
    int shiftBS(vector<int>& nums, int pivot, int target) {
        int n = nums.size();
        int shift = n - pivot;
        int left = (pivot + shift) % n;
        int right = (pivot - 1 + shift) % n;

        while (left <= right) {
            int mid = (left + right) / 2;
            //because the mid meant the position in unrotated array, 
            //for retrieving value in a rotated array, we should use shifted mid position.
            //so how to get it? use the shifted smallest position(pivot)!!
            int shifted_mid = (mid + pivot) % n;

            if (nums[shifted_mid] == target) {
                return shifted_mid;
            } else if (nums[shifted_mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return -1;
    }

    int bs(vector<int>& nums, int left, int right, int target) {
        int L = left;
        int R = right;

        while (L <= R) {
            int mid = (L + R) / 2;

            if (nums[mid] == target){
                return mid;
            } else if (nums[mid] > target) {
                R = mid - 1;
            } else {
                L = mid + 1;
            }
        }

        return -1;
    }

public:
    int search(vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }

        if (nums.size() == 1) {
            return nums[0] == target ? 0 : -1;
        }

        int len = nums.size();
        int begin = 0;
        int end = len - 1;

        //one time binary search
        while (begin <= end) {
            int mid = begin + (end - begin) / 2;

            
            if (nums[mid] == target) {
                //case 1: find target
                return mid;

            } else if (nums[mid] >= nums[begin]) {
                //case 2: sub-array on the left of mid is sorted
                if (target >= nums[begin] && target < nums[mid]) {
                    end = mid - 1;
                } else {
                    begin = mid + 1;
                }

            } else {
                //case 3: sub-array one the right of mid is sorted
                if (target <= nums[end] && target > nums[mid]) {
                    begin = mid + 1;
                } else {
                    end = mid - 1;
                }
            }
        }

        return -1;

        /*
        //find smallest
        while (begin <= end) {
            int mid = (begin + end) / 2;

            if (nums[mid] > nums[len - 1]) {
                begin = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        //using shift binary search
        return shiftBS(nums, begin, target);
        */

        //split two part to search
        /*
        //when upper loop ends, we will have the position of smallest element
        int result = bs(nums, 0, begin - 1, target);
        if (result != -1) {
            return result;
        }

        return bs(nums, begin, len - 1, target);
        */
    }
};