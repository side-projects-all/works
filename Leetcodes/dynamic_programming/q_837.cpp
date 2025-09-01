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
        if (k == 0 || n >= k - 1 + maxPts) {
            return 1.0;
        }

        std::vector<double> dp(n + 1);
        dp[0] = 1.0;
        
        //P(x) = 1/W * (P(x-1) + P(x-2) + P(x-W)) = 1/W * sumP(x-W, x-1)
        //P[i] = 1/W * sum[i-1]
        //sum[i] = sum[i-1] + P[i] = sum[i-1] + sum[i-1] / W     (when i <= W)
        double sum = 1.0;
        double ans = 0.0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = sum / maxPts;

            if (i < k) {
                sum += dp[i];   //keep drawing, so add to sum
            } else {
                ans += dp[i];   // i >= k, add to final ans
            }

            if (i - maxPts >= 0 && i - maxPts < k) {    //out of window size
                sum -= dp[i - maxPts];
            }
        }

        return ans;
        
        /*
        std::vector<double> dp(n + 1, 0.0);
        dp[0] = 1.0;

        for (int i = 0; i < k; ++i) {                       // only < K keep drawing
            double p = dp[i] / maxPts;                      // split evenly to next W
            for (int x = 1; x <= maxPts; ++x) {
                int j = i + x;
                if (j <= n) dp[j] += p;                     // stop accumulating after N
            }
        }

        double ans = 0.0;
        for (int i = k; i <= n; ++i) ans += dp[i];
        return ans;
        */
    }
public:
    double new21Game(int n, int k, int maxPts) {
        return iterative(n, k, maxPts);
    }
};