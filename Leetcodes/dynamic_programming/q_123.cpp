/*
You are given an array prices where prices[i] is the price of a given stock on the ith day.

Find the maximum profit you can achieve. You may complete at most two transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [3,3,5,0,0,3,1,4]
Output: 6
Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

Example 2:

Input: prices = [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple transactions at the same time. You must sell before buying again.

Example 3:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.

 

Constraints:

    1 <= prices.length <= 10^5
    0 <= prices[i] <= 10^5


*/

class Solution {
private:
    int by_itertive_dp(vector<int>& prices) {
        int n = prices.size();
        if (n == 1) {
            return 0;
        }

        std::vector<int> max_profit1(n);
        int min_cost1 = prices[0];
        std::vector<int> max_profit2(n + 1);
        int max_price2 = prices[n - 1];

        for (int i = 1; i < n; ++i) {
            max_profit1[i] = std::max(max_profit1[i - 1], prices[i] - min_cost1);
            min_cost1 = std::min(min_cost1, prices[i]);

            int r = n - i - 1;
            //pass from right to left
            max_profit2[r] = std::max(max_profit2[r + 1], max_price2 - prices[r]);
            max_price2 = std::max(max_price2, prices[r]);
        }

        int max_profit = 0;
        for (int i = 0; i < n; ++i) {
            max_profit = std::max(max_profit, max_profit1[i] + max_profit2[i + 1]);
        }

        return max_profit;
    }
    int by_optimize_itertive_dp(vector<int>& prices) {
        int n = prices.size();
        if (n == 1) {
            return 0;
        }

        int cost1 = prices[0];
        int profit1 = 0;
        int cost2 = prices[0];
        int profit2 = 0;

        for (int i = 1; i < n; ++i) {
            cost1 = std::min(cost1, prices[i]);
            profit1 = std::max(profit1, prices[i] - cost1);

            cost2 = std::min(cost2, prices[i] - profit1);
            profit2 = std::max(profit2, prices[i] - cost2);
        }

        return profit2;
    }
public:
    int maxProfit(vector<int>& prices) {
        return by_itertive_dp(prices);
        
        //return by_optimize_itertive_dp(prices);
    }
};