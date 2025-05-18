/*
You are given an integer array nums and two integers minK and maxK.

A fixed-bound subarray of nums is a subarray that satisfies the following conditions:

    The minimum value in the subarray is equal to minK.
    The maximum value in the subarray is equal to maxK.

Return the number of fixed-bound subarrays.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2
Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].

Example 2:

Input: nums = [1,1,1,1], minK = 1, maxK = 1
Output: 10
Explanation: Every subarray of nums is a fixed-bound subarray. There are 10 possible subarrays.

 

Constraints:

    2 <= nums.length <= 10^5
    1 <= nums[i], minK, maxK <= 10^6


*/

class Solution {
private:
    long long by_sliding_window(vector<int>& nums, int minK, int maxK) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] == minK == maxK;
        }

        int b = -1;
        int e = 0;
        int min_pos = -1;
        int max_pos = -1;
        long long cnt = 0;
        while (e < n) {
            if (nums[e] > maxK || nums[e] < minK) {
                b = e;
            }

            if (nums[e] == maxK) {
                max_pos = e;
            }

            if (nums[e] == minK) {
                min_pos = e;
            }

            cnt += std::max(0, std::min(max_pos, min_pos) - b);
            ++e;
        }

        return cnt;
    }
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        return by_sliding_window(nums, minK, maxK);
    }
};