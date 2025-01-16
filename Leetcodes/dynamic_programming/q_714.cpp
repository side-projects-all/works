/*
You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.

Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

Example 1:

Input: prices = [1,3,2,8,4,9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
- Buying at prices[0] = 1
- Selling at prices[3] = 8
- Buying at prices[4] = 4
- Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

Example 2:

Input: prices = [1,3,7,5,10,3], fee = 3
Output: 6

Constraints:

    1 <= prices.length <= 5 * 10^4
    1 <= prices[i] < 5 * 10^4
    0 <= fee < 5 * 10^4

*/

class Solution {
private:
    int iterative_space_optimize(vector<int>& prices, int fee) {
        int n = prices.size();
        if (n == 1) {
            return 0;
        }

        int sold = 0;
        int hold = -prices[0] - fee;

        for (int i = 1; i < n; ++i) {

            hold = std::max(hold, sold - prices[i] - fee);
            sold = std::max(sold, hold + prices[i]);
        }

        return sold;
        /*
        int N = prices.size();
        //still another state transition

        //start from 1
        int free = 0;
        int hold = -prices[0];

        for (int i = 1; i < N; ++i) {
            int prehold = hold;
            hold = std::max(hold, free - prices[i]);
            free = std::max(free, prehold + prices[i] - fee);
        }
        */

        //start from 0
        /*
        int free = 0;
        int hold = -50000;

        for (int i = 0; i < N; ++i) {
            int prehold = hold;
            hold = std::max(hold, free - prices[i]);
            free = std::max(free, prehold + prices[i] - fee);
        }
        */

        //return free;
    }

    int iterative(vector<int>& prices, int fee) {
        int N = prices.size();
        std::vector<int> free(N, 0);
        std::vector<int> hold(N, 0);

        hold[0] = -prices[0];

        for (int i = 1; i < N; ++i) {
            free[i] = std::max(free[i - 1], hold[i - 1] + prices[i] - fee);
            hold[i] = std::max(hold[i - 1], free[i - 1] - prices[i]);
        }

        return free[N - 1];
    }

    int recursive(vector<int>& prices, int fee) {
        return -1;
    }

public:
    int maxProfit(vector<int>& prices, int fee) {
        //return recursive(prices, fee);
        //return iterative(prices, fee);
        return iterative_space_optimize(prices, fee);
    }
};