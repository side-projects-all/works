/*
188. Best Time to Buy and Sell Stock IV

You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

constraints:
    0 <= k <= 100
    0 <= prices.length <= 1000
    0 <= prices[i] <= 1000

ex1:
Input: k = 2, prices = [2,4,1]
Output: 2
Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

ex2:
Input: k = 2, prices = [3,2,6,5,0,3]
Output: 7
Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
*/

class Solution {
private:
    int iterative_onePass(int k, vector<int>& prices) {
        if (k == 0) {
            return 0;
        }
        int N = prices.size();

        std::vector<int> profits(k + 1, 0);
        std::vector<int> costs(k + 1, INT_MAX);

        for (int p : prices) {
            for (int i = 0; i < k; ++i) {
                costs[i + 1] = std::min(costs[i + 1], p - profits[i]);
                profits[i + 1] = std::max(profits[i + 1], p - costs[i + 1]);
            }
        }

        return profits[k];
    }
    int iterative(int k, vector<int>& prices) {

        int N = prices.size();
        if (N <= 1) {
            return 0;
        }

        //corner case: transaction times is larger than the length of prices
        if (k * 2 >= N) {
            int r = 0;

            for (int i = 1; i < N; ++i) {
                r += std::max(0, prices[i] - prices[i - 1]);
            }

            return r;
        }

        //this means mem[day_number][used_transaction_number][stock_holding_status]
        std::vector<std::vector<std::vector<int>>> mem(N, std::vector<std::vector<int>>(k + 1, 
                                                                            std::vector<int>(2, -1000001)));

        mem[0][0][0] = 0;
        mem[0][1][1] = -prices[0];

        for (int i = 1; i < N; ++i) {
            for (int j = 0; j <= k; ++j) {

                //for selling case: do selling or not holding
                //mem[i][j][0]: selling profit
                //Keep not holding the stock : mem[i][j][0] = mem[i−1][j][0]
                //Selling : mem[i][j][0] = mem[i−1][j][1] + prices[i]
                mem[i][j][0] = std::max(mem[i - 1][j][0], mem[i - 1][j][1] + prices[i]);

                //for buying case: do buying or keep holding
                //mem[i][j][1]: holding cost
                if (j > 0) {
                    //Keep holding the stock : mem[i][j][1] = mem[i−1][j][1]
                    //Buying, when j > 0 : mem[i][j][1] = mem[i−1][j−1][0] − prices[i]
                    mem[i][j][1] = std::max(mem[i - 1][j][1], mem[i - 1][j - 1][0] - prices[i]);
                }
            }
        }

        int maxProfit = 0;
        for (int i = 0; i <= k; ++i) {
            maxProfit = std::max(maxProfit, mem[N - 1][i][0]);
        }
        

        return maxProfit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        //return iterative(k, prices);
        return iterative_onePass(k, prices);
    }
};