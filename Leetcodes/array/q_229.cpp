/*
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]

Example 2:

Input: nums = [1]
Output: [1]

Example 3:

Input: nums = [1,2]
Output: [1,2]

 

Constraints:

    1 <= nums.length <= 5 * 10^4
    -10^9 <= nums[i] <= 10^9

*/

class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        if (nums.size() == 1) {
            return nums;
        }

        int n = nums.size();
        /* naive
        std::unordered_set<int> tmp;
        std::unordered_map<int, int> m;

        for (int i = 0; i < n; ++i) {

            ++m[nums[i]];
            if (m[nums[i]] > n / 3) {
                tmp.insert(nums[i]);
            }
        }

        return std::vector<int>(tmp.begin(), tmp.end());
        */

        //Boyer-Moore Voting Algorithm
        //1st pass
        int cnt1 = 0;
        int cnt2 = 0;

        int candi01 = INT_MIN;
        int candi02 = INT_MIN;

        for (int n : nums) {
            if (candi01 != INT_MIN && candi01 == n) {
                ++cnt1;
            } else if (candi02 != INT_MIN && candi02 == n) {
                ++cnt2;
            } else if (cnt1 == 0) {
                candi01 = n;
                ++cnt1;
            } else if (cnt2 == 0) {
                candi02 = n;
                ++cnt2;
            } else {
                --cnt1;
                --cnt2;
            }
        }

        std::vector<int> ans;
        int sec_cnt1 = 0;
        int sec_cnt2 = 0;

        for (int n : nums) {
            if (candi01 == n) {
                ++sec_cnt1;
            }

            if (candi02 == n) {
                ++sec_cnt2;
            }
        }

        int len = nums.size();
        if (sec_cnt1 > n / 3) {
            ans.push_back(candi01);
        }

        if (sec_cnt2 > n / 3) {
            ans.push_back(candi02);
        }

        return ans;
    }
};