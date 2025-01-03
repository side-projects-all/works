/*
You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:

    The length of the subarray is k, and
    All the elements of the subarray are distinct.

Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

Example 2:

Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.

 

Constraints:

    1 <= k <= nums.length <= 10^5
    1 <= nums[i] <= 10^5


*/

class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        
        std::unordered_map<int, int> num_to_i;
        int b = 0;
        int e = 0;
        long long max_sum = 0;
        long long curr_sum = 0;

        while (e < nums.size()) {
            int curr = nums[e];
            int showed_at = (num_to_i.find(curr) != num_to_i.end() ? num_to_i[curr] : -1);
            
            //the current number had showed before, then we need to move b forward, or 
            //the window was larger than k
            while (b <= showed_at || e - b + 1 > k) {
                curr_sum -= nums[b];
                ++b;
            }
            
            num_to_i[curr] = e; //update the index of current number
            curr_sum += nums[e];

            if (e - b + 1 == k) {
                max_sum = std::max(max_sum, curr_sum);
            }
            
            ++e;
        }

        return max_sum;
    }
};