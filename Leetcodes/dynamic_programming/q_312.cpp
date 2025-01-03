/*
You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

 

Example 1:

Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

Example 2:

Input: nums = [1,5]
Output: 10

 

Constraints:

    n == nums.length
    1 <= n <= 300
    0 <= nums[i] <= 100


*/

class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.emplace_back(1);

        std::vector<std::vector<int>> dp(nums.size(), std::vector<int>(nums.size(), 0));
        for (int left = nums.size() - 2; left >= 1; --left) {
            for (int right = left; right <= nums.size() - 2; ++right) {
                
                for (int i = left; i <= right; ++i) {
                    //this means we gain as last step
                    int gain = nums[left - 1] * nums[i] * nums[right + 1];
                    int remaining = dp[left][i - 1] + dp[i + 1][right];

                    dp[left][right] = std::max(dp[left][right], remaining + gain);
                }
            }
        }

        return dp[1][nums.size() - 2];
    }
};