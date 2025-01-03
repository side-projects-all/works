/*
Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.

Return any array that satisfies this condition.

 

Example 1:

Input: nums = [3,1,2,4]
Output: [2,4,3,1]
Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.

Example 2:

Input: nums = [0]
Output: [0]

 

Constraints:

    1 <= nums.length <= 5000
    0 <= nums[i] <= 5000


*/

class Solution {
private:
    std::vector<int> inplace(std::vector<int>& nums) {
        int odd = 0;
        int even = nums.size() - 1;

        while (odd < even) {
            //find 
            if (nums[odd] % 2 != 0 && nums[even] % 2 == 0) {
                int tmp = nums[odd];
                nums[odd] = nums[even];
                nums[even] = tmp;
                ++odd;
                --even;
                continue;
            }

            if (nums[odd] % 2 == 0) {
                ++odd;
            }
            if (nums[even] % 2 != 0) {
                --even;
            }
        }

        return nums;
    }

public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        return inplace(nums);
    }
};