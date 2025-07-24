/*
You are given an array of positive integers nums and want to erase a subarray containing unique elements. The score you get by erasing the subarray is equal to the sum of its elements.

Return the maximum score you can get by erasing exactly one subarray.

An array b is called to be a subarray of a if it forms a contiguous subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some (l,r).

 

Example 1:

Input: nums = [4,2,4,5,6]
Output: 17
Explanation: The optimal subarray here is [2,4,5,6].

Example 2:

Input: nums = [5,2,1,2,5,2,1,2,5]
Output: 8
Explanation: The optimal subarray here is [5,2,1] or [1,2,5].

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^4


*/

class Solution {
private:
    int by_sliding_window(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int curr_sum = 0;
        int p1 = 0;
        std::vector<bool> used(10001);

        for (int i = 0; i < n; ++i) {
            
            while (used[nums[i]]) {
                used[nums[p1]] = false;
                curr_sum -= nums[p1];
                ++p1;
            }

            used[nums[i]] = true;
            curr_sum += nums[i];
            ans = std::max(ans, curr_sum);
        }

        return ans;
    }
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        return by_sliding_window(nums);
    }
};