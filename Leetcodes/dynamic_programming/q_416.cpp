/*
Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

 

Example 1:

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:

Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.

 

Constraints:

    1 <= nums.length <= 200
    1 <= nums[i] <= 100


*/

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return false;
        }

        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2) {
            return false;
        }
        
        int subset_sum(sum / 2);
        std::vector<std::vector<int>> mem(n + 1, std::vector<int>(subset_sum + 1, -1));
        
        int ans = recursive(n - 1, subset_sum, mem, nums);
        return ans > 0 ? true : false;
    }

private:
    int recursive(int len, int subset_sum, std::vector<std::vector<int>>& mem, std::vector<int>& nums) {
        if (subset_sum == 0) {
            return 1;
        }

        if (len == 0 || subset_sum < 0) {
            return 0;
        }

        if (mem[len][subset_sum] != -1) {
            return mem[len][subset_sum];
        }

        int ans = recursive(len - 1, subset_sum - nums[len - 1], mem, nums) || 
                     recursive(len - 1, subset_sum, mem, nums);

        return mem[len][subset_sum] = ans;
    }
};