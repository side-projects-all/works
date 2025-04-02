/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

 

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1

Example 3:

Input: coins = [1], amount = 0
Output: 0

 

Constraints:

    1 <= coins.length <= 12
    1 <= coins[i] <= 2^31 - 1
    0 <= amount <= 10^4


*/

class Solution {
private:
  int iterative(vector<int>& coins, int amount) {
    if (amount == 0) {
        return 0;
    }

    int n = coins.size();
    if (n == 1) {
        if (coins[0] == 1) {
            return amount;
        }
        return amount % coins[0] != 0 ? -1 : amount / coins[0];
    }

    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;

    for (int a = 1; a <= amount; ++a) {
        for (int i = 0; i < n; ++i) {

            if (a < coins[i]) {
                continue;
            }
            dp[a] = std::min(dp[a], 1 + dp[a - coins[i]]);
        }
    }

    return dp[amount] > amount ? -1 : dp[amount];
  }
  int recursive(vector<int>& coins, int amount, std::vector<int>& mem) {
    if (amount < 0) {
        return -1;
    }

    if (amount == 0) {
        return 0;
    }

    if (mem[amount] != -2) {
        return mem[amount];
    }

    int min = INT_MAX;
    for (int i = 0; i < coins.size(); ++i) {

      int val = recursive(coins, amount - coins[i], mem);
          
      if (val >= 0 && val < min) {
          min = 1 + val;
      }
    }

    mem[amount] = (min == INT_MAX) ? -1 : min;
    return mem[amount];
  }
public:
  int coinChange(vector<int>& coins, int amount) {
    if (amount < 1) {
        return 0;
    }

    //use -2 because -1 would become value of some cases in mem
    //std::vector<int> mem(amount + 1, -2);
    //return recursive(coins, amount, mem);

    return iterative(coins, amount);
  }
};