/*
Given an integer array nums and an integer k, return the length of the shortest non-empty subarray of nums with a sum of at least k. If there is no such subarray, return -1.

A subarray is a contiguous part of an array.

 

Example 1:

Input: nums = [1], k = 1
Output: 1

Example 2:

Input: nums = [1,2], k = 4
Output: -1

Example 3:

Input: nums = [2,-1,2], k = 3
Output: 3

 

Constraints:

    1 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5
    1 <= k <= 10^9


*/

class Solution {
public:
    int shortestSubarray(vector<int>& nums, int targetSum) {
        size_t n = nums.size();

        // Size is n+1 to handle subarrays starting from index 0
        std::vector<long long> prefix_sums(n + 1, 0);

        // Calculate prefix sums
        for (size_t i = 1; i <= n; ++i) {
            prefix_sums[i] = prefix_sums[i - 1] + nums[i - 1];
        }

        std::deque<int> possible;

        int min_len = INT_MAX;

        for (size_t i = 0; i <= n; i++) {

            while (!possible.empty() && prefix_sums[i] - prefix_sums[possible.front()] >= targetSum) {

                min_len = std::min(min_len, (int)i - possible.front());
                possible.pop_front();
            }

            while (!possible.empty() && prefix_sums[i] <= prefix_sums[possible.back()]) {
                possible.pop_back();
            }

            possible.push_back(i);
        }

        return min_len == INT_MAX ? -1 : min_len;
    }
};