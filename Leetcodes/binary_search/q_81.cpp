/*
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.

You must decrease the overall operation steps as much as possible.

 

Example 1:

Input: nums = [2,5,6,0,0,1,2], target = 0
Output: true

Example 2:

Input: nums = [2,5,6,0,0,1,2], target = 3
Output: false

 

Constraints:

    1 <= nums.length <= 5000
    -10^4 <= nums[i] <= 10^4
    nums is guaranteed to be rotated at some pivot.
    -10^4 <= target <= 10^4

 

Follow up: This problem is similar to Search in Rotated Sorted Array, but nums may contain duplicates. Would this affect the runtime complexity? How and why?

*/

class Solution {
private:
    bool by_binary_search(vector<int>& nums, int& target) {
      int n = nums.size();
      if (n == 1) {
          return nums[0] == target;
      }

      int left = 0;
      int right = n - 1;

      while (left <= right) {
          while (left < right && nums[left] == nums[left + 1]) {
              ++left;
          }

          while (right > left && nums[right - 1] == nums[right]) {
              --right;
          }

          int mid = left + (right - left) / 2;

          if (nums[mid] == target) {
              return true;
          }

          //separate two parts: first part non-descending ordered or else
          if (nums[left] <= nums[mid]) {
              //check if target in first part or else
              if (target >= nums[left] && target < nums[mid]) {
                  right = mid - 1;
              } else {
                  left = mid + 1;
              }

          } else {
              if (target > nums[mid] && target <= nums[right]) {
                  left = mid + 1;
              } else {
                  right = mid - 1;
              }
          }
      }

      return false;
    }
public:
    bool search(vector<int>& nums, int target) {
        
        /*
        int N = nums.size();
        if (N == 1) {
            return nums[0] == target;
        }
        int left = 0;
        int right = N - 1;
        
        std::function<bool(int, int, int)> bs = [&](int begin, int end, int goal) -> bool {

            while (begin <= end) {
                while (begin < end && nums[begin] == nums[begin + 1]) {
                    ++begin;
                }

                while (begin < end && nums[end] == nums[end - 1]) {
                    --end;
                }

                int mid = begin + (end - begin) / 2;

                if (nums[mid] == goal) {
                    return true;
                }

                if (nums[mid] >= nums[begin]) {
                    if (goal >= nums[begin] && goal < nums[mid]) {
                        end = mid - 1;
                    } else {
                        begin = mid + 1;
                    }
                    
                } else {
                    if (goal <= nums[end] && goal > nums[mid]) {
                        begin = mid + 1;
                        
                    } else {
                        end = mid - 1;
                    }
                }
            }

            return false;
        };
        
        return bs(left, right, target);
        */
        
        return by_binary_search(nums, target);
    }
};