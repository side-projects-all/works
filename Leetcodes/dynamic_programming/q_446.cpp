/*
Given an integer array nums, return the number of all the arithmetic subsequences of nums.

A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

    For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
    For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.

A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.

    For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].

The test cases are generated so that the answer fits in 32-bit integer.

 

Example 1:

Input: nums = [2,4,6,8,10]
Output: 7
Explanation: All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]

Example 2:

Input: nums = [7,7,7,7,7]
Output: 16
Explanation: Any subsequence of this array is arithmetic.

 

Constraints:

    1  <= nums.length <= 1000
    -2^31 <= nums[i] <= 2^31 - 1


*/

class Solution {
private:
    int by_iterative_dp(vector<int>& nums) {
        int n = nums.size();
        if (n < 3) {
            return 0;
        }

        if (n == 3) {
            return ((long)nums[1] - nums[0]) == ((long)nums[2] - nums[1]);
        }

        std::vector<std::vector<int>> dp(n, std::vector<int>(n));
        std::unordered_map<int, std::vector<int>> num_to_index;
        for (int i = 0; i < n; ++i) {
            num_to_index[nums[i]].push_back(i);
        }

        int ans = 0;
        for (int k = 2; k < n; ++k) {
            for (int j = 1; j < k; ++j) {

                long nums_i = 2L * nums[j] - nums[k];
                if (nums_i > INT_MAX || nums_i < INT_MIN) {
                    continue;
                }

                if (num_to_index.find(nums_i) != num_to_index.end()) {
                    for (const auto& i : num_to_index[nums_i]) {

                        if (i >= j) {
                            break;
                        }

                        dp[k][j] += dp[j][i] + 1;
                    }
                }

                ans += dp[k][j];
            }
        }

        return ans;
    }
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        return by_iterative_dp(nums);
    }
};