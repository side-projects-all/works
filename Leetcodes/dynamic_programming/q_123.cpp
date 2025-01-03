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
    int iterative_optimize(vector<int>& prices) {
        int t1Cost = 100001;
        int t2Cost = 100001;
        int t1Profit = 0;
        int t2Profit = 0;

        for (int p : prices) {
            t1Cost = std::min(t1Cost, p);
            t1Profit = std::max(t1Profit, p - t1Cost);

            t2Cost = std::min(t2Cost, p - t1Profit);
            t2Profit = std::max(t2Profit, p - t2Cost);
        }

        return t2Profit;
    }

    int iterative(vector<int>& prices) {
        int N = prices.size();
        if (N <= 1) {
            return 0;
        }

        int leftMin = prices[0];
        int rightMax = prices[N - 1];

        std::vector<int> leftProfits(N, 0);
        std::vector<int> rightProfits(N + 1, 0);

        for (int left = 1; left < N; ++left) {
            leftProfits[left] = std::max(leftProfits[left - 1], prices[left] - leftMin);
            leftMin = std::min(leftMin, prices[left]);

            int r = N - 1 - left;
            rightProfits[r] = std::max(rightProfits[r + 1], rightMax - prices[r]);
            rightMax = std::max(rightMax, prices[r]);
        }

        int maxProfit = 0;
        for (int i = 0; i < N; ++i) {
            //why left and right would be i and i + 1?
            //because left i means max profit for selling at i day, 
            //and i + 1 means the begin of second transaction at i + 1 day!!
            maxProfit = std::max(maxProfit, leftProfits[i] + rightProfits[i + 1]);
        }

        return maxProfit;
    }
public:
    int maxProfit(vector<int>& prices) {
        //return iterative(prices);
        return iterative_optimize(prices);
    }
};