/*
You are given an array of integers nums and an integer target.

Return the number of non-empty subsequences of nums such that the sum of the minimum and maximum element on it is less or equal to target. Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: nums = [3,5,6,7], target = 9
Output: 4
Explanation: There are 4 subsequences that satisfy the condition.
[3] -> Min value + max value <= target (3 + 3 <= 9)
[3,5] -> (3 + 5 <= 9)
[3,5,6] -> (3 + 6 <= 9)
[3,6] -> (3 + 6 <= 9)

Example 2:

Input: nums = [3,3,6,8], target = 10
Output: 6
Explanation: There are 6 subsequences that satisfy the condition. (nums can have repeated numbers).
[3] , [3] , [3,3], [3,6] , [3,6] , [3,3,6]

Example 3:

Input: nums = [2,3,3,4,6,7], target = 12
Output: 61
Explanation: There are 63 non-empty subsequences, two of them do not satisfy the condition ([6,7], [7]).
Number of valid subsequences (63 - 2 = 61).

 

Constraints:

    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6
    1 <= target <= 10^6


*/

class Solution {
private:
    int byTwoPointer(vector<int>& nums, int target) {
        int MOD = 1'000'000'007;
        int N = nums.size();
        std::sort(nums.begin(), nums.end());

        std::vector<int> possibility(N);
        possibility[0] = 1;
        for (int i = 1; i < N; ++i) {
            possibility[i] = (possibility[i - 1] * 2) % MOD;
        }

        int ans = 0;
        int left  = 0;
        int right = N - 1;
        while (left <= right) {
            if (nums[left] + nums[right] <= target) {
                ans += possibility[right - left];
                ans %= MOD;
                ++left;

            } else {
                --right;
            }
        }

        return ans;
    }
    int byBS(vector<int>& nums, int target) {
        
        int MOD = 1'000'000'007;
        int N = nums.size();
        std::sort(nums.begin(), nums.end());

        std::vector<int> possibility(N);
        possibility[0] = 1;
        for (int i = 1; i < N; ++i) {
            possibility[i] = (possibility[i - 1] * 2) % MOD;
        }

        int ans = 0;
        for (int i = 0; i < N; ++i) {
            int rest = target - nums[i];
            int left = i;
            int right = N - 1;

            //search the element that is smaller than or equal to rest
            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (nums[mid] <= rest) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }

            right = left - 1;

            if (right >= i) {
                ans += possibility[right - i];
                ans %= MOD;
            }
        }

        return ans;
    }
public:
    int numSubseq(vector<int>& nums, int target) {
        //corner case
        if (nums.size() == 1) {
            return nums[0] * 2 <= target ? 1 : 0;
        }

        //return byBS(nums, target);
        return byTwoPointer(nums, target);
    }
};