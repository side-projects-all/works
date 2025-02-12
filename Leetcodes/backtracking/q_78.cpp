/*
Given an integer array nums of unique elements, return all possible
subsets
(the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:

Input: nums = [0]
Output: [[],[0]]

 

Constraints:

    1 <= nums.length <= 10
    -10 <= nums[i] <= 10
    All the numbers of nums are unique.


*/

class Solution {
private:
    void back_tracking(vector<int>& nums, std::vector<std::vector<int>>& ans, int i, vector<int>&& curr) {
        ans.push_back(curr);

        for (int j = i; j < nums.size(); ++j) {
            curr.push_back(nums[j]);
            back_tracking(nums, ans, j + 1, std::move(curr));
            curr.pop_back();
        }
    }
    vector<vector<int>> by_back_tracking(vector<int>& nums) {
        std::vector<std::vector<int>> ans;

        back_tracking(nums, ans, 0, std::vector<int>());
        return ans;
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return by_back_tracking(nums);
    }
};
/*
class Solution {
private:
    std::vector<std::vector<int>> backtracking(vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        ans.push_back(std::vector<int>());
        std::vector<int> curr;

        std::function<void(int, int)> bt = [&](int i, int len) {
            if (i == len) {
                ans.push_back(curr);
                return;
            }

            for (int j = i; j < nums.size(); ++j) {
                curr.push_back(nums[j]);
                bt(j + 1, len);
                curr.pop_back();
            }
        };

        for (int l = 1; l <= nums.size(); ++l) {
            curr.clear();
            bt(0, l);
        }

        return ans;
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        return backtracking(nums);
    }
};
*/