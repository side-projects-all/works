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
private:
    int recursive(vector<int>& nums, std::vector<std::vector<int>>& mem, int b, int e) {
        if (b > e) {
            return 0;
        }

        if (mem[b][e] != -1) {
            return mem[b][e];
        }

        for (int i = b; i <= e; ++i) {
            int gain = nums[b - 1] * nums[i] * nums[e + 1];
            int remain = recursive(nums, mem, b, i - 1) + recursive(nums, mem, i + 1, e);

            mem[b][e] = std::max(mem[b][e], gain + remain);
        }

        return mem[b][e];
    }
    int by_recursive_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }

        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        n += 2;

        std::vector<std::vector<int>> mem(n, std::vector<int>(n, -1));

        return recursive(nums, mem, 1, n - 2);
    }
    int by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return nums[0];
        }

        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        n += 2;

        std::vector<std::vector<int>> dp(n, std::vector<int>(n));

        for (int b = n - 2; b >= 1; --b) {
            for (int e = b; e <= n - 2; ++e) {

                for (int i = b; i <= e; ++i) {
                    //using b-1, e+1 means nums[i] is burst at last
                    int gain = nums[b - 1] * nums[i] * nums[e + 1];
                    int remain = dp[b][i - 1] + dp[i + 1][e];

                    dp[b][e] = std::max(dp[b][e], gain + remain);
                }
            }
        }

        return dp[1][n - 2];
    }
public:
    int maxCoins(vector<int>& nums) {
        return by_iterative_dp(nums);
        //return by_recursive_dp(nums);
    }
};