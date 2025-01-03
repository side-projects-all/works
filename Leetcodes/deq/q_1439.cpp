/*
Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 

Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.

Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.

Example 3:

Input: nums = [4,2,2,2,4,4,2,2], limit = 0
Output: 3

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^9
    0 <= limit <= 10^9


*/

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        if (nums.size() < 2) {
            return 1;
        }

        int longest = 0;
        int b = 0;
        std::deque<int> max_dq;
        std::deque<int> min_dq;

        for (int e = 0; e < nums.size(); ++e) {
            
            while (!max_dq.empty() && max_dq.back() < nums[e]) {
                max_dq.pop_back();
            }
            max_dq.push_back(nums[e]);

            while (!min_dq.empty() && min_dq.back() > nums[e]) {
                min_dq.pop_back();
            }
            min_dq.push_back(nums[e]);

            while (max_dq.front() - min_dq.front() > limit) {

                if (max_dq.front() == nums[b]) {
                    max_dq.pop_front();
                }

                if (min_dq.front() == nums[b]) {
                    min_dq.pop_front();
                }

                ++b;
            }

            longest = std::max(longest, e - b + 1);
        }

        return longest;
    }
};