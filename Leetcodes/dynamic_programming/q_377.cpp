/*
Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.

The test cases are generated so that the answer can fit in a 32-bit integer.

 

Example 1:

Input: nums = [1,2,3], target = 4
Output: 7
Explanation:
The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
Note that different sequences are counted as different combinations.

Example 2:

Input: nums = [9], target = 3
Output: 0

 

Constraints:

    1 <= nums.length <= 200
    1 <= nums[i] <= 1000
    All the elements of nums are unique.
    1 <= target <= 1000

*/

class Solution {
private:
    int iterative(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) {
            return target % nums[0] == 0;
        }

        std::vector<unsigned int> dp(target + 1);
        dp[0] = 1;

        for (int v = 1; v <= target; ++v) {
            for (int i = 0; i < n; ++i) {

                if (nums[i] <= v) {
                    dp[v] += dp[v - nums[i]];
                }
            }
        }

        return dp[target];
    }

    int recursive(vector<int>& nums, int target, std::vector<int>& mem) {
        if (target == 0) {
            return 1;
        }

        if (mem[target] != -1) {
            return mem[target];
        }

        int val = 0;
        for (int n : nums) {
            if (n <= target) {
                val += recursive(nums, target - n, mem);
            }
        }

        mem[target] = val;
        return val;
    }
public:
    int combinationSum4(vector<int>& nums, int target) {
        //std::vector<int> mem(target + 1, -1);
        //return recursive(nums, target, mem);
        return iterative(nums, target);
    }
};