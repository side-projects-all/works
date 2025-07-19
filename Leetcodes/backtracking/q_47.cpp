/*
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

 

Example 1:

Input: nums = [1,1,2]
Output:
[[1,1,2],
 [1,2,1],
 [2,1,1]]

Example 2:

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

 

Constraints:

    1 <= nums.length <= 8
    -10 <= nums[i] <= 10


*/

class Solution {
private:
    void backtracking(std::unordered_map<int, int>& cnts, int& n, std::vector<std::vector<int>>& ans, 
        vector<int>&& curr) {
        if (curr.size() == n) {
            ans.push_back(curr);
            return;
        }

        for (auto& p : cnts) {
            if (p.second == 0) continue;

            --cnts[p.first];
            curr.push_back(p.first);
            backtracking(cnts, n, ans, std::move(curr));
            curr.pop_back();
            ++cnts[p.first];
        }
    }

    vector<vector<int>> by_backtracking(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) {
            return { nums };
        }

        std::unordered_map<int, int> cnts;
        for (int i = 0; i < n; ++i) {
            ++cnts[nums[i]];
        }

        std::vector<std::vector<int>> ans;
        backtracking(cnts, n, ans, {});
        return ans;
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        return by_backtracking(nums);
    }
};

/*
class Solution {
private:
    vector<vector<int>> backtrack(vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        std::unordered_map<int, int> m;
        int N = nums.size();

        for (int v : nums) {
            ++m[v];
        }

        std::vector<int> combination;
        std::function<void()> bt = [&]() {
            if (combination.size() == N) {
                ans.push_back(combination);
                return;
            }

            for (auto& p : m) {
                int n = p.first;
                int cnt = p.second;

                if (cnt == 0) {
                    continue;
                }

                combination.push_back(n);
                --m[n];

                bt();

                combination.pop_back();
                ++m[n];
            }
        };

        bt();

        return ans;
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        return backtrack(nums);
    }
};
*/