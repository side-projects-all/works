/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:

Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

 

Constraints:

    1 <= k <= 100
    1 <= prices.length <= 1000
    0 <= prices[i] <= 1000


*/

class Solution {
private:
    int by_iterative_dp(int& k, vector<int>& prices) {
        int n = prices.size();
        if (n == 1) {
            return 0;
        }

        if (2 * n < k) {
            return 0;
        }

        std::vector<int> costs(k + 1, 1001);
        costs[1] = prices[0];
        std::vector<int> profits(k + 1);

        for (int i = 1; i < n; ++i) {
            for (int t = 1; t <= k; ++t) {
                costs[t] = std::min(costs[t], prices[i] - profits[t - 1]);
                profits[t] = std::max(profits[t], prices[i] - costs[t]);
            }
        }
        /*
        for (int i = 1; i < n; ++i) {
            for (int t = 0; t < k; ++t) {
                costs[t + 1] = std::min(costs[t + 1], prices[i] - profits[t]);
                profits[t + 1] = std::max(profits[t + 1], prices[i] - costs[t + 1]);
            }
        }
        */

        return profits[k];
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        return by_iterative_dp(k, prices);
    }
};