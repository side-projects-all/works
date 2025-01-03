/*
Given an array of integers nums and an integer k. A continuous subarray is called nice if there are k odd numbers on it.

Return the number of nice sub-arrays.

 

Example 1:

Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The only sub-arrays with 3 odd numbers are [1,1,2,1] and [1,2,1,1].

Example 2:

Input: nums = [2,4,6], k = 1
Output: 0
Explanation: There are no odd numbers in the array.

Example 3:

Input: nums = [2,2,2,1,2,2,1,2,2,2], k = 2
Output: 16

 

Constraints:

    1 <= nums.length <= 50000
    1 <= nums[i] <= 10^5
    1 <= k <= nums.length


*/

class Solution {
private:
    int prefix_sum_position(vector<int>& nums, int k) {
        int len = 0;
        int sub = 0;
        int b = 0;

        for (int e = 0; e < nums.size(); ++e) {
            len += nums[e] % 2;

            while (len > k) {
                len -= nums[b] % 2;
                ++b;
            }

            sub += e - b + 1;
        }

        return sub;
    }
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        return prefix_sum_position(nums, k) - prefix_sum_position(nums, k - 1);
    }
};