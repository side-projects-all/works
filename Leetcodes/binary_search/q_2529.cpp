/*
Given an array nums sorted in non-decreasing order, return the maximum between the number of positive integers and the number of negative integers.

    In other words, if the number of positive integers in nums is pos and the number of negative integers is neg, then return the maximum of pos and neg.

Note that 0 is neither positive nor negative.

 

Example 1:

Input: nums = [-2,-1,-1,1,2,3]
Output: 3
Explanation: There are 3 positive integers and 3 negative integers. The maximum count among them is 3.

Example 2:

Input: nums = [-3,-2,-1,0,0,1,2]
Output: 3
Explanation: There are 2 positive integers and 3 negative integers. The maximum count among them is 3.

Example 3:

Input: nums = [5,20,66,1314]
Output: 4
Explanation: There are 4 positive integers and 0 negative integers. The maximum count among them is 4.

 

Constraints:

    1 <= nums.length <= 2000
    -2000 <= nums[i] <= 2000
    nums is sorted in a non-decreasing order.

*/

class Solution {
private:
    int by_binary_search(std::vector<int>& nums) {
        int n = nums.size();
        int b = 0;
        int e = n - 1;

        //find negative end
        while (b <= e) {
            int mid = b + (e - b) / 2;

            if (nums[mid] >= 0) {
                e = mid - 1;
            } else {
                
                b = mid + 1;
            }
        }

        int neg = b;
        
        e = n - 1;
        while (b <= e) {
            int mid = b + (e - b) / 2;

            if (nums[mid] > 0) {
                e = mid - 1;
            } else {
                
                b = mid + 1;
            }
        }

        int pos = n - b;

        return pos > neg ? pos : neg;
    }
public:
    Solution() {}
    ~Solution() {}

    int maximumCount(std::vector<int>& nums) {
        return by_binary_search(nums);
    }
};