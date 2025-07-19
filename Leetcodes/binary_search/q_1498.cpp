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
    int by_ptr(vector<int>& nums, int& target) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] * 2 <= target;
        }

        std::sort(nums.begin(), nums.end());
        std::vector<int> possibility(n);
        possibility[0] = 1;
        for (int i = 1; i < n; ++i) {
            possibility[i] = (possibility[i - 1] * 2) % 1'000'000'007;
        }

        int cnt = 0;
        int b = 0;
        int e = n - 1;
        while (b <= e) {

            if (nums[b] + nums[e] <= target) {
                cnt = (cnt + possibility[e - b]) % 1'000'000'007;
                ++b;

            } else {
                --e;
            }
        }

        return cnt;
    }
    int by_bs(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] * 2 <= target;
        }

        std::sort(nums.begin(), nums.end());
        std::vector<int> possibility(n);
        possibility[0] = 1;
        for (int i = 1; i < n; ++i) {
            possibility[i] = (possibility[i - 1] * 2) % 1'000'000'007;
        }

        int cnt = 0;
        for (int i = 0; i < n; ++i) {

            if (target < nums[i]) {
                break;
            }
            int b = 0;
            int e = n - 1;
            int rest = target - nums[i];

            while (b <= e) {
                int mid = b + (e - b) / 2;

                if (nums[mid] <= rest) {
                    b = mid + 1;
                } else {
                    e = mid - 1;
                }
            }

            b -= 1;
            if (b >= i) {
                cnt = (cnt + possibility[b - i]) % 1'000'000'007;
            }
        }

        return cnt;
    }
public:
    int numSubseq(vector<int>& nums, int target) {
        //return by_bs(nums, target);
        return by_ptr(nums, target);
    }
};