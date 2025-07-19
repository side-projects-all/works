/*
You are given an integer array nums.

A

sub of nums with length x is called valid if it satisfies:

    (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.

Return the length of the longest valid subsequence of nums.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

 

Example 1:

Input: nums = [1,2,3,4]

Output: 4

Explanation:

The longest valid subsequence is [1, 2, 3, 4].

Example 2:

Input: nums = [1,2,1,1,2,1,2]

Output: 6

Explanation:

The longest valid subsequence is [1, 2, 1, 2, 1, 2].

Example 3:

Input: nums = [1,3]

Output: 2

Explanation:

The longest valid subsequence is [1, 3].

 

Constraints:

    2 <= nums.length <= 2 * 10^5
    1 <= nums[i] <= 10^7

*/

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int n = nums.size();
        if (n == 2) {
            return 2;
        }
        
        int dp[2][2]{0};
        int max_len = 0;
        for (int i = 0; i < n; ++i) {

            int curr = nums[i] % 2;
            for (int prev = 0; prev < 2; ++prev) {
                dp[prev][curr] = dp[curr][prev] + 1;
                max_len = std::max(max_len, dp[prev][curr]);
            }
        }

        return max_len;
        /*
        int ans = 0;
        int pattern[4][2]{ {0, 0}, {0, 1}, {1, 0}, {1, 1} };
        for (auto& p : pattern) {

            int cnt = 0;
            for (int n : nums) {
                if (n % 2 == p[cnt % 2]) {
                    ++cnt;
                }
            }

            ans = std::max(ans, cnt);
        }

        return ans;
        */

        /*
        int odds = (nums[0] % 2 == 1) ? 1 : 0;  //for all odds {1, 1}
        int evens = (nums[0] % 2 == 0) ? 1 : 0; //for all evens {0, 0}
        int diff = 1;   //for combination of {0, 1} or {1, 0}
        for (int i = 1; i < n; ++i) {
            if (nums[i - 1] % 2 != (nums[i] % 2)) {
                ++diff;
            }

            if (nums[i] % 2 == 0) {
                ++evens;
            } else {
                ++odds;
            }
        }

        return std::max({diff, evens, odds});
        */
    }
};