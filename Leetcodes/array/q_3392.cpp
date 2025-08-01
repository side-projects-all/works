/*
Given an integer array nums, return the number of

of length 3 such that the sum of the first and third numbers equals exactly half of the second number.

 

Example 1:

Input: nums = [1,2,1,4,1]

Output: 1

Explanation:

Only the subarray [1,4,1] contains exactly 3 elements where the sum of the first and third numbers equals half the middle number.

Example 2:

Input: nums = [1,1,1]

Output: 0

Explanation:

[1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.

 

Constraints:

    3 <= nums.length <= 100
    -100 <= nums[i] <= 100

*/

class Solution {
public:
    int countSubarrays(vector<int>& nums) {
        int cnt = 0;
        for (int i = 2; i < nums.size(); ++i) {
            if ((nums[i - 2] + nums[i]) * 2 == nums[i - 1]) {
                ++cnt;
            }
        }

        return cnt;
    }
};