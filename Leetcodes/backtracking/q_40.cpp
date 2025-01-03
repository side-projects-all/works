/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.

 

Example 1:

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: 
[
[1,1,6],
[1,2,5],
[1,7],
[2,6]
]

Example 2:

Input: candidates = [2,5,2,1,2], target = 5
Output: 
[
[1,2,2],
[5]
]

 

Constraints:

    1 <= candidates.length <= 100
    1 <= candidates[i] <= 50
    1 <= target <= 30


*/

class Solution {
private:
    vector<vector<int>> backtracking(vector<int>& candidates, int target) {
        int N = candidates.size();
        std::sort(candidates.begin(), candidates.end());
        std::vector<std::vector<int>> ans;
        
        std::vector<int> combine;
        std::function<void(int, int)> bt = [&](int i, int rest) {
            if (rest == 0) {
                ans.push_back(combine);
                return;

            }

            for (int now = i; now < N; ++now) {
                if (candidates[now] > rest) {
                    return;
                }
                if (now > i && candidates[now] == candidates[now - 1]) {
                    continue;
                }

                combine.push_back(candidates[now]);
                bt(now + 1, rest - candidates[now]);
                combine.pop_back();
            }
        };

        bt(0, target);

        return ans;
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        return backtracking(candidates, target);
    }
};