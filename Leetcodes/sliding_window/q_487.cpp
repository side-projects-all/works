/*
Given a binary array nums, return the maximum number of consecutive 1's in the array if you can flip at most one 0.

 

Example 1:

Input: nums = [1,0,1,1,0]
Output: 4
Explanation: 
- If we flip the first zero, nums becomes [1,1,1,1,0] and we have 4 consecutive ones.
- If we flip the second zero, nums becomes [1,0,1,1,1] and we have 3 consecutive ones.
The max number of consecutive ones is 4.

Example 2:

Input: nums = [1,0,1,1,0,1]
Output: 4
Explanation: 
- If we flip the first zero, nums becomes [1,1,1,1,0,1] and we have 4 consecutive ones.
- If we flip the second zero, nums becomes [1,0,1,1,1,1] and we have 4 consecutive ones.
The max number of consecutive ones is 4.

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums.length <= 10^5
    nums[i] is either 0 or 1.

*/

class Solution {
private:
    int by_sliding_window(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return 1;
        }

        int b = 0;
        int e = 0;
        int longest = 0;
        int zeros = 0;
        while (e < n) {
            if (nums[e] == 0) {
                ++zeros;
            }

            if (zeros <= 1) {
                longest = std::max(longest, e - b + 1);

            } else {
                while (zeros > 1) {
                    if (nums[b] == 0) {
                        --zeros;
                    }

                    ++b;
                }
            }

            ++e;
        }

        return longest;
    }
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        return by_sliding_window(nums);
    }
};