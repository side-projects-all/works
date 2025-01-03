/*
Given an integer array nums and an integer k, return the maximum length of a
subarray
that sums to k. If there is not one, return 0 instead.

 

Example 1:

Input: nums = [1,-1,5,-2,3], k = 3
Output: 4
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.

Example 2:

Input: nums = [-2,-1,2,1], k = 1
Output: 2
Explanation: The subarray [-1, 2] sums to 1 and is the longest.

 

Constraints:

    1 <= nums.length <= 2 * 10^5
    -10^4 <= nums[i] <= 10^4
    -10^9 <= k <= 10^9


*/

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int max_len = 0;
        long prefix_sum = 0;
        std::unordered_map<long, int> m;

        for (int i = 0; i < nums.size(); ++i) {

            prefix_sum += nums[i];
            //because of zero index
            if (prefix_sum == k) {
                max_len = i + 1;
            }

            //this means we fidn the begin index
            if (m.find(prefix_sum - k) != m.end()) {
                max_len = std::max(max_len, i - m[prefix_sum - k]);
            }

            //not update the index in the hash map because we want the longest subarray
            if (m.find(prefix_sum) == m.end()) {
                m[prefix_sum] = i;
            }
        }

        return max_len;
    }
};