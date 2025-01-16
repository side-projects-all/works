/*
Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.

Note that:

    A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
    A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).

 

Example 1:

Input: nums = [3,6,9,12]
Output: 4
Explanation:  The whole array is an arithmetic sequence with steps of length = 3.

Example 2:

Input: nums = [9,4,7,2,10]
Output: 3
Explanation:  The longest arithmetic subsequence is [4,7,10].

Example 3:

Input: nums = [20,1,15,3,10,5,8]
Output: 4
Explanation:  The longest arithmetic subsequence is [20,15,10,5].

 

Constraints:

    2 <= nums.length <= 1000
    0 <= nums[i] <= 500


*/

class Solution {
private:
    int iterative(vector<int>& nums) {
        int N = nums.size();
        int max = 0;

        std::vector<std::vector<int>> mem(N, std::vector<int>(1002, 1));
        int ans = 0;
        for (int i = 1; i < N; ++i) {

            for (int j = 0; j < i; ++j) {
                int diff = nums[i] - nums[j] + 500;

                mem[i][diff] = std::max(mem[i][diff], 1 + mem[j][diff]);
                ans = std::max(ans, mem[i][diff]);
            }            
        }

        return ans;
        /*
        std::vector<std::unordered_map<int, int>> map(nums.size());
        for (int i = 1; i < nums.size(); ++i) {

            for (int j = 0; j < i; ++j) {
                int diff = nums[j] - nums[i];

                if (map[j].find(diff) == map[j].end()) {
                    map[j][diff] = 1;
                } 
                map[i][diff] = (map[j][diff] + 1);

                max = std::max(max, map[i][diff]);
            }
        }
        
        return max;
        */
    }

public:
    int longestArithSeqLength(vector<int>& nums) {
        return iterative(nums);
    }
};