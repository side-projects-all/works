/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.


ex1:
Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1

ex2:
Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.

ex3:
Input: amount = 10, coins = [10]
Output: 1

Constraints:

    1 <= coins.length <= 300
    1 <= coins[i] <= 5000
    All the values of coins are unique.
    0 <= amount <= 5000


*/

class Solution {
private:
    int iterative_space_optimize(int amount, vector<int>& coins) {
        if (amount == 0) {
            return 1;
        }

        std::vector<unsigned int> dp(amount + 1);
        dp[0] = 1;

        for (int i = 0; i < coins.size(); ++i) {
            for (int a = coins[i]; a <= amount; ++a) {
                dp[a] += dp[a - coins[i]];
            }
        }

        return dp[amount];
    }

    int iterative(int amount, vector<int>& coins) {
        int N = coins.size();
        std::vector<std::vector<int>> mem(N + 1, std::vector<int>(amount + 1));
        for (int i = 0; i < N; ++i) {
            mem[i][0] = 1;
        }

        for (int i = N - 1; i >= 0; --i) {
            for (int j = 1; j <= amount; ++j) {
                if (coins[i] > j) {
                    mem[i][j] = mem[i + 1][j];
                } else {
                    mem[i][j] = mem[i + 1][j] + mem[i][j - coins[i]];
                }
            }
        }

        return mem[0][amount];
    }

    int recursive(int amount, vector<int>& coins, int i, std::vector<std::vector<int>>& mem) {
        if (amount == 0) {
            return 1;
        }

        if (i == coins.size()) {
            return 0;
        }

        if (mem[i][amount] != -1) {
            return mem[i][amount];
        }

        int val = 0;
        if (coins[i] > amount) {
            val = recursive(amount, coins, i + 1, mem);
        } else {
            val = recursive(amount - coins[i], coins, i, mem) + recursive(amount, coins, i + 1, mem);
        }

        mem[i][amount] = val;

        return val;
    }
    
public:
    int change(int amount, vector<int>& coins) {
        //std::vector<std::vector<int>> mem(coins.size(), std::vector<int>(amount + 1, -1));

        //return recursive(amount, coins, 0, mem);
        //return iterative(amount, coins);

        return iterative_space_optimize(amount, coins);
    }
};