/*
Given an integer array nums, find the maximum possible bitwise OR of a subset of nums and return the number of different non-empty subsets with the maximum bitwise OR.

An array a is a subset of an array b if a can be obtained from b by deleting some (possibly zero) elements of b. Two subsets are considered different if the indices of the elements chosen are different.

The bitwise OR of an array a is equal to a[0] OR a[1] OR ... OR a[a.length - 1] (0-indexed).

 

Example 1:

Input: nums = [3,1]
Output: 2
Explanation: The maximum possible bitwise OR of a subset is 3. There are 2 subsets with a bitwise OR of 3:
- [3]
- [3,1]

Example 2:

Input: nums = [2,2,2]
Output: 7
Explanation: All non-empty subsets of [2,2,2] have a bitwise OR of 2. There are 23 - 1 = 7 total subsets.

Example 3:

Input: nums = [3,2,1,5]
Output: 6
Explanation: The maximum possible bitwise OR of a subset is 7. There are 6 subsets with a bitwise OR of 7:
- [3,5]
- [3,1,5]
- [3,2,5]
- [3,2,1,5]
- [2,5]
- [2,1,5]

 

Constraints:

    1 <= nums.length <= 16
    1 <= nums[i] <= 10^5


*/

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        
        int n = nums.size();
        int or_all = 0;
        for (int val : nums) {
            or_all |= val;
        }
        

        //std::vector<std::vector<int>> mem(n, std::vector<int>(or_all + 1, -1));

        //return mem_backtracking(nums, mem, or_all, 0, 0);

        //return iterative(nums);
        int cnt = 0;
        recursive(nums, cnt, or_all, 0, 0);

        return cnt;
    }

private:
    void recursive(vector<int>& nums, int& cnt, int target_or, int curr_or, int i) {
        if (curr_or == target_or) {
            cnt += 1 << (nums.size() - i);
            return;
        }

        if (i == nums.size()) {
            return;
        }

        //not use this one
        recursive(nums, cnt, target_or, curr_or, i + 1);
        //use this one
        recursive(nums, cnt, target_or, curr_or | nums[i], i + 1);
    }
    int iterative(vector<int>& nums) {
        int max_or = 0;
        std::vector<int> dp(1 << 17, 0);

        dp[0] = 1;

        for (int n : nums) {
            for (int i = max_or; i >= 0; --i) {
                dp[i | n] += dp[i];
            }

            max_or |= n;
        }

        return dp[max_or];
    }

    int mem_backtracking(vector<int>& nums, std::vector<std::vector<int>>& mem, int& target_or, int i, int curr_or) {
        if (i == nums.size()) {
            return curr_or == target_or;
        }

        if (mem[i][curr_or] != -1) {
            return mem[i][curr_or];
        }

        int not_use = mem_backtracking(nums, mem, target_or, i + 1, curr_or);
        int use = mem_backtracking(nums, mem, target_or, i + 1, curr_or | nums[i]);

        return mem[i][curr_or] = not_use + use;
    }
};
