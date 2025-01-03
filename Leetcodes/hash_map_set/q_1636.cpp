/*
Given an array of integers nums, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.

Return the sorted array.

 

Example 1:

Input: nums = [1,1,2,2,2,3]
Output: [3,1,1,2,2,2]
Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.

Example 2:

Input: nums = [2,3,1,3,2]
Output: [1,3,3,2,2]
Explanation: '2' and '3' both have a frequency of 2, so they are sorted in decreasing order.

Example 3:

Input: nums = [-1,1,-6,4,5,-6,1,4,1]
Output: [5,-1,4,4,-6,-6,1,1,1]

 

Constraints:

    1 <= nums.length <= 100
    -100 <= nums[i] <= 100


*/

class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        std::unordered_map<int, int> m;

        for (int i = 0; i < nums.size(); ++i) {
            ++m[nums[i]];
        }

        std::vector<std::pair<int, int>> cnts_vals;
        for (const auto& p : m) {
            cnts_vals.push_back({p.second, p.first});
        }

        std::sort(cnts_vals.begin(), cnts_vals.end(), 
                    [](const auto& p1, const auto& p2) {
                        if (p1.first == p2.first) {
                            return p1.second > p2.second;
                        }

                        return p1.first < p2.first;
                    });

        std::vector<int> ans(nums.size());
        int j = 0;

        for (const auto& p : cnts_vals) {
            for (int i = 0; i < p.first; ++i) {
                ans[j] = p.second;
                ++j;
            }
        }

        return ans;
    }
};