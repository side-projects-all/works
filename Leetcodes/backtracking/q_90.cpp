/*
Given an integer array nums that may contain duplicates, return all possible
subsets
(the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

 

Example 1:

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:

Input: nums = [0]
Output: [[],[0]]

 

Constraints:

    1 <= nums.length <= 10
    -10 <= nums[i] <= 10


*/

class Solution {
private:
    void back_tracking(vector<int>& nums, std::vector<std::vector<int>>& ans, int i, std::vector<int>&& curr) {
        ans.push_back(curr);

        for (int j = i; j < nums.size(); ++j) {
            if (j > i && nums[j] == nums[j - 1]) {
                continue;
            }

            curr.push_back(nums[j]);
            back_tracking(nums, ans, j + 1, std::move(curr));
            curr.pop_back();
        }
    }
    vector<vector<int>> by_back_tracking(vector<int>& nums) {
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans;

        back_tracking(nums, ans, 0, std::vector<int>());

        return ans;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        return by_back_tracking(nums);
    }
};

/*
class Solution {
private:
    vector<vector<int>> backtracking(vector<int>& nums) {
        int N = nums.size();
        //corner case
        if (N == 1) {
            return {{}, nums};
        }

        //we need to omit the duplicate subsets, so we sort
        std::sort(nums.begin(), nums.end());
        std::vector<int> curr{};
        std::vector<std::vector<int>> ans{};

        std::function<void(int)> bt = [&](int i) {
            ans.push_back(curr);

            for (int now = i; now < N; ++now) {
                if (now != i && nums[now] == nums[now - 1]) {
                    continue;
                }

                curr.push_back(nums[now]);
                bt(now + 1);
                curr.pop_back();
            }
        };

        bt(0);

        return ans;
    }
    vector<vector<int>> cascading(vector<int>& nums) {
        int N = nums.size();
        //corner case
        if (N == 1) {
            return {{}, nums};
        }

        //we need to omit the duplicate subsets, so we sort
        std::sort(nums.begin(), nums.end());
        std::vector<std::vector<int>> ans{{}};
        int len = 0;

        for (int i = 0; i < N; ++i) {
            //if it were a repetitive value, we add it into previous array
            int begin = (i >= 1 && nums[i] == nums[i - 1]) ? len : 0;

            len = ans.size();
            for (int b = begin; b < len; ++b) {
                std::vector<int> curr = ans[b];
                curr.push_back(nums[i]);
                ans.push_back(curr);
            }
        }

        return ans;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        
        //return cascading(nums);
        return backtracking(nums);
    }
};
*/