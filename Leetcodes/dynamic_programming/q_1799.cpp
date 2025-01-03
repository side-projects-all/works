/*
You are given nums, an array of positive integers of size 2 * n. You must perform n operations on this array.

In the ith operation (1-indexed), you will:

    Choose two elements, x and y.
    Receive a score of i * gcd(x, y).
    Remove x and y from nums.

Return the maximum score you can receive after performing n operations.

The function gcd(x, y) is the greatest common divisor of x and y.

 

Example 1:

Input: nums = [1,2]
Output: 1
Explanation: The optimal choice of operations is:
(1 * gcd(1, 2)) = 1

Example 2:

Input: nums = [3,4,6,8]
Output: 11
Explanation: The optimal choice of operations is:
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11

Example 3:

Input: nums = [1,2,3,4,5,6]
Output: 14
Explanation: The optimal choice of operations is:
(1 * gcd(1, 5)) + (2 * gcd(2, 4)) + (3 * gcd(3, 6)) = 1 + 4 + 9 = 14

 

Constraints:

    1 <= n <= 7
    nums.length == 2 * n
    1 <= nums[i] <= 10^6


*/

class Solution {
private:
    int recursive(vector<int>& nums) {
        int N = nums.size();
        int len = 1 << N;
        std::vector<int> mem(len, -1);

        std::function<int(int, int)> backtrack = [&](int mask, int pairsPicked) -> int {
            if (2 * pairsPicked == N) {
                return 0;
            }

            if (mem[mask] != -1) {
                return mem[mask];
            }

            int maxScore = 0;
            for (int f = 0; f < N; ++f) {
                for (int s = f + 1; s < N; ++s) {
                    /*
                    if (((mask >> f) & 1) == 1 || ((mask >> s) & 1) == 1) {
                        continue;
                    }*/

                    //same meanings as above
                    if ((mask & (1 << f)) != 0 || (mask & (1 << s)) != 0 ) {
                        continue;
                    }

                    int newMask = mask | (1 << f) | (1 << s);
                    int currScore = (pairsPicked + 1) * __gcd(nums[f], nums[s]);
                    int restScore = backtrack(newMask, pairsPicked + 1);

                    maxScore = std::max(maxScore, currScore + restScore);
                }
            }

            return mem[mask] = maxScore;
        };

        return backtrack(0, 0);
    }
public:
    int maxScore(vector<int>& nums) {
        return recursive(nums);
    }
};