/*
Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:

    answer[i] % answer[j] == 0, or
    answer[j] % answer[i] == 0

If there are multiple solutions, return any of them.

 

Example 1:

Input: nums = [1,2,3]
Output: [1,2]
Explanation: [1,3] is also accepted.

Example 2:

Input: nums = [1,2,4,8]
Output: [1,2,4,8]

 

Constraints:

    1 <= nums.length <= 1000
    1 <= nums[i] <= 2 * 10^9
    All the integers in nums are unique.


*/

class Solution {
private:
    vector<int> iterative(vector<int>& nums) {

        int N = nums.size();
        if (N == 0) {
            return {};
        }

        std::sort(nums.begin(), nums.end());
        std::vector<int> mem(N, 1);
        int maxi = 1;

        for (int i = 1; i < N; ++i) {

            for (int j = 0; j < i; ++j) {
                if (nums[i] % nums[j] == 0 && mem[i] < mem[j] + 1) {
                    mem[i] = mem[j] + 1;
                    
                    if (maxi < mem[i]) {
                        maxi = mem[i];
                    }
                }
            }
        }

        int num = -1;
        std::vector<int> ans;
        for (int i = N - 1; i >= 0; --i) {
            if (maxi == mem[i] && (num == -1 || num % nums[i] == 0)) {
                ans.push_back(nums[i]);
                --maxi;
                num = nums[i];
            }
        }

        return ans;
        /*
        int N = nums.size();
        if (N == 0) {
            return {};
        }

        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> allPossible(N, std::vector<int>());

        for (int i = 0; i < N; ++i) {
            std::vector<int> maxSub;

            for (int k = 0; k < i; ++k) {
                if (nums[i] % nums[k] == 0 && maxSub.size() < allPossible[k].size()) {
                    maxSub = allPossible[k];
                }
            }

            if (maxSub.size() > 0) {
                allPossible[i].insert(allPossible[i].end(), maxSub.begin(), maxSub.end());
            }
            
            allPossible[i].emplace_back(nums[i]);
        }

        std::vector<int> ans;
        for (int i = 0; i < N; ++i) {
            if (ans.size() < allPossible[i].size()) {
                ans = allPossible[i];
            }
        }

        return ans;
        */
    }
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        return iterative(nums);
    }
};