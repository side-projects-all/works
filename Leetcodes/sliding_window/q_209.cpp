/*
Given an array of positive integers nums and a positive integer target, return the minimal length of a
subarray
whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.

 

Example 1:

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:

Input: target = 4, nums = [1,4,4]
Output: 1

Example 3:

Input: target = 11, nums = [1,1,1,1,1,1,1,1]
Output: 0

 

Constraints:

    1 <= target <= 10^9
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4

*/

class Solution {
private:
    int by_sliding_window(int& target, vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] > target;
        }
        int b = 0;
        int e = 0;
        int sum = 0;
        int min_len = INT_MAX;
        while (e < n) {
            if (sum < target) {
                sum += nums[e];
            }

            while (b <= e && sum >= target) {
                min_len = std::min(min_len, e - b + 1);

                sum -= nums[b];
                ++b;
            }

            ++e;
        }

        return b == 0 && sum < target ? 0 : min_len;
    }
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        return by_sliding_window(target, nums);
    }
};