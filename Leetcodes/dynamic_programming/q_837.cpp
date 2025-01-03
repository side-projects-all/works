/*
Alice plays the following game, loosely based on the card game "21".

Alice starts with 0 points and draws numbers while she has less than k points. During each draw, she gains an integer number of points randomly from the range [1, maxPts], where maxPts is an integer. Each draw is independent and the outcomes have equal probabilities.

Alice stops drawing numbers when she gets k or more points.

Return the probability that Alice has n or fewer points.

Answers within 10-5 of the actual answer are considered accepted.

 

Example 1:

Input: n = 10, k = 1, maxPts = 10
Output: 1.00000
Explanation: Alice gets a single card, then stops.

Example 2:

Input: n = 6, k = 1, maxPts = 10
Output: 0.60000
Explanation: Alice gets a single card, then stops.
In 6 out of 10 possibilities, she is at or below 6 points.

Example 3:

Input: n = 21, k = 17, maxPts = 10
Output: 0.73278

 

Constraints:

    0 <= k <= n <= 10^4
    1 <= maxPts <= 10^4


*/

class Solution {
private:
    double iterative(int n, int k, int maxPts) {
        if (k == 0 || n >= k + maxPts) {
            return 1.0;
        }

        std::vector<double> dp(n + 1);
        dp[0] = 1.0;
        
        double sum = 1.0;
        double ans = 0.0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = sum / maxPts;

            if (i < k) {
                sum += dp[i];
            } else {
                ans += dp[i];
            }

            if (i - maxPts >= 0) {
                sum -= dp[i - maxPts];
            }
        }

        return ans;
        /*
        std::vector<double> dp(n + maxPts, 0.0);
        for (int i = k; i <= n; ++i) {
            dp[i] = 1.0;
        }

        //using n = 21, k = 17, maxPts = 10 to think about it
        //when you arrive k, you could not draw, and the point must smaller than or equal to n!!!
        //so we count every number of them as 1 
        //ex: 17, 18, 19, 20, 21
        //dp[k] means the probability from k you will be smaller than or equal to 21

        double s = std::min((n - k + 1.0), (double)maxPts);
        //we start from k - 1
        for (int r = k - 1; r > -1; --r) {
            
            double tmp = 0.0;
            for (int i = 0; i < maxPts; ++i) {
                tmp += dp[r + i + 1];
            }

            dp[r] = tmp / (1.0 * maxPts);
            

            //those are improved from upper part
            //dp[r] = s / maxPts;
            //s = s + dp[r] - dp[r + maxPts];
        }

        return dp[0];
        */
    }
public:
    double new21Game(int n, int k, int maxPts) {
        return iterative(n, k, maxPts);
    }
};