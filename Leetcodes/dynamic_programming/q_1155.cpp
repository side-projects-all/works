/*
You have n dice and each die has k faces numbered from 1 to k.

Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice so the sum of the face-up numbers equals target. Since the answer may be too large, return it modulo 109 + 7.

 

Example 1:

Input: n = 1, k = 6, target = 3
Output: 1
Explanation: You throw one die with 6 faces.
There is only one way to get a sum of 3.

Example 2:

Input: n = 2, k = 6, target = 7
Output: 6
Explanation: You throw two dice, each with 6 faces.
There are 6 ways to get a sum of 7: 1+6, 2+5, 3+4, 4+3, 5+2, 6+1.

Example 3:

Input: n = 30, k = 30, target = 500
Output: 222616187
Explanation: The answer must be returned modulo 109 + 7.

 

Constraints:

    1 <= n, k <= 30
    1 <= target <= 1000

*/

class Solution {
private:
    int iterative(int n, int k, int target) {
        std::vector<std::vector<int>> mem(n + 1, std::vector<int>(target + 1, 0));

        mem[0][0] = 1;

        
        for (int dice = 1; dice <= n; ++dice) {
            for (int rest = 1; rest <= target; ++rest) {
                int cnt = 0;

                for (int face = 1; face <= std::min(k, rest); ++face) {
                    cnt = (cnt + mem[dice - 1][rest - face]) % 1000000007;
                }

                mem[dice][rest] = cnt;
            }
        }

        return mem[n][target];
    }
    int recursive(int n, int k, int target, std::vector<std::vector<int>>& mem) {
        //base case
        if (n == 0) {
            if (target == 0) {
                return 1;
            } else {
                return 0;
            }
        }

        if (mem[n][target] != -1) {
            return mem[n][target];
        }

        int cnt = 0;
        for (int i = 1; i <= std::min(k, target); ++i) {
            cnt = (cnt + recursive(n - 1, k, target - i, mem)) % 1000000007;
        }
        /*
        for (int i = 1; i <= k; ++i) {
            if (target - i >= 0) {
                cnt = (cnt + recursive(n - 1, k, target - i, mem)) % 1000000007;
            } 
        }
        */

        mem[n][target] = cnt;

        return mem[n][target];
    }

public:
    int numRollsToTarget(int n, int k, int target) {
        //std::vector<std::vector<int>> mem(n + 1, std::vector<int>(target + 1, -1));

        //int val = recursive(n, k, target, mem);
        //return val;

        return iterative(n, k, target);
    }
};