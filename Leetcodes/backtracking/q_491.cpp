/*
Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.

 

Example 1:

Input: nums = [4,6,7,7]
Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]

Example 2:

Input: nums = [4,4,3,2,1]
Output: [[4,4]]

 

Constraints:

    1 <= nums.length <= 15
    -100 <= nums[i] <= 100


*/

class Solution {
private:
    std::vector<std::vector<int>> by_bitmask(std::vector<int>& nums) {
        
        int n = nums.size();
        std::set<std::vector<int>> candidate; //using set do not need to create custome hash function
        
        for (int possible = 2; possible < (1 << n); ++possible) {

            std::vector<int> seq;
            for (int i = 0; i < n; ++i) {
  
                if ((possible >> i) & 1) {

                    if (seq.empty() || nums[i] >= seq.back()) {
                        seq.push_back(nums[i]);
                    }
                }
            }

            if (seq.size() >= 2) {
                candidate.insert(seq);
            }
        }

        return std::vector<std::vector<int>>(candidate.begin(), candidate.end());
    }
    
    void backtracking(std::set<std::vector<int>>& all, std::vector<int>& seq, std::vector<int>& nums, int i) {
        if (i == nums.size()) {
            if (seq.size() >= 2) {
                all.insert(seq);
            }

            return;
        }

        if (seq.empty() || seq.back() <= nums[i]) {
            seq.push_back(nums[i]);

            backtracking(all, seq, nums, i + 1);

            seq.pop_back();
        }

        backtracking(all, seq, nums, i + 1);
    }

    std::vector<std::vector<int>> by_backtracking(std::vector<int>& nums) {
        std::set<std::vector<int>> all; //using set do not need to create custome hash function
        std::vector<int> seq;

        backtracking(all, seq, nums, 0);

        return std::vector<std::vector<int>>(all.begin(), all.end());
    }
    
public:
    std::vector<std::vector<int>> findSubsequences(std::vector<int>& nums) {
        return by_backtracking(nums);
        //return by_bitmask(nums);
    }
};