/*
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.

Return the single element that appears only once.

Your solution must run in O(log n) time and O(1) space.

 

Example 1:

Input: nums = [1,1,2,3,3,4,4,8,8]
Output: 2

Example 2:

Input: nums = [3,3,7,7,10,11,11]
Output: 10

 

Constraints:

    1 <= nums.length <= 10^5
    0 <= nums[i] <= 10^5


*/

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        /*
        int N = nums.size();
        int left = 0;
        int right = N - 1;


        while (left < right) {
            int mid = left + (right - left) / 2;
            bool isHalfEven = (right - mid) % 2 == 0;

            if (nums[mid + 1] == nums[mid]) {
                if (isHalfEven) {
                    left = mid + 2;
                } else {
                    right =  mid - 1;
                }
                
            } else if (nums[mid - 1] == nums[mid]){
                if (isHalfEven) {
                    right =  mid - 2;
                } else {
                    left = mid + 1;
                }

            } else {
                return nums[mid];
            }
        }

        return nums[left];
        */

        //better version
        int lo = 0;
        int hi = nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mid % 2 == 1) mid--;
            if (nums[mid] == nums[mid + 1]) {
                lo = mid + 2;
            } else {
                hi = mid;
            }
        }
        return nums[lo];
    }
};