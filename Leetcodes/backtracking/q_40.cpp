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
    void back_tracking(vector<int>& candidates, int& target, std::vector<std::vector<int>>& ans, int i, int sum, std::vector<int>&& curr) {

        if (sum == target) {
            ans.push_back(curr);
            return;
        }

        if (sum > target || i >= candidates.size()) {
            return;
        }

        for (int j = i; j < candidates.size(); ++j) {
            if (candidates[j] > target) {
                return;
            }

            if (j > i && candidates[j] == candidates[j - 1]) {
                continue;
            }

            curr.push_back(candidates[j]);
            back_tracking(candidates, target, ans, j + 1, sum + candidates[j], std::move(curr));
            curr.pop_back();
        }
    }
    vector<vector<int>> by_back_tracking(vector<int>& candidates, int& target) {
        std::vector<std::vector<int>> ans;
        std::sort(candidates.begin(), candidates.end());

        back_tracking(candidates, target, ans, 0, 0, std::vector<int>());
        return ans;
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        return by_back_tracking(candidates, target);
    }
};