/*
There are two types of soup: type A and type B. Initially, we have n ml of each type of soup. There are four kinds of operations:

    Serve 100 ml of soup A and 0 ml of soup B,
    Serve 75 ml of soup A and 25 ml of soup B,
    Serve 50 ml of soup A and 50 ml of soup B, and
    Serve 25 ml of soup A and 75 ml of soup B.

When we serve some soup, we give it to someone, and we no longer have it. Each turn, we will choose from the four operations with an equal probability 0.25. If the remaining volume of soup is not enough to complete the operation, we will serve as much as possible. We stop once we no longer have some quantity of both types of soup.

Note that we do not have an operation where all 100 ml's of soup B are used first.

Return the probability that soup A will be empty first, plus half the probability that A and B become empty at the same time. Answers within 10-5 of the actual answer will be accepted.

 

Example 1:

Input: n = 50
Output: 0.62500
Explanation: If we choose the first two operations, A will become empty first.
For the third operation, A and B will become empty at the same time.
For the fourth operation, B will become empty first.
So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.

Example 2:

Input: n = 100
Output: 0.71875

 

Constraints:

    0 <= n <= 10^9


*/

class Solution {
private:
    double by_recursive_dp(int& n) {
        // For large n the probability is within 1e-5 of 1.0
        if (n >= 4800) return 1.0;

        // Work in units of 25 mL
        int m = (n + 24) / 25;  // ceil(n/25)
        std::vector<std::vector<double>> dp(m + 1, std::vector<double>(m + 1, -1.0));

        std::function<double(int,int)> f = [&](int a, int b) -> double {
            if (a <= 0 && b <= 0) return 0.5; // both empty same turn
            if (a <= 0) return 1.0;           // A empty first
            if (b <= 0) return 0.0;           // B empty first
            double &res = dp[a][b];
            if (res >= 0.0) return res;
            
            res = 0.25 * (f(a - 4, b) + f(a - 3, b - 1) + f(a - 2, b - 2) + f(a - 1, b - 3));
            return res;
        };

        return f(m, m);
    }
    double by_iterative_dp(int& n) {
        if (n > 4800) return 1.0;

        int m = std::ceil(n / 25.0);
        // it means how the maximum times after n divided by 25
        // dp array means the output result
        // (the expectation of the probability that A is used up before B, 
        // and the probability that both soups are used up in the same turn)
        std::vector<std::vector<double>> dp(m + 1, std::vector<double>(m + 1));   

        dp[0][0] = 0.5;
        //different combination of times after n divided by 25, max only 199, because rest are 1.0
        for (int t1 = 1; t1 <= m; ++t1) {
            dp[0][t1] = 1;
            dp[t1][0] = 0;

            for (int t2 = 1; t2 <= t1; ++t2) {
                dp[t1][t2] = (dp[std::max(0, t1 - 4)][t2] + dp[std::max(0, t1 - 3)][t2 - 1] + 
                            dp[std::max(0, t1 - 2)][std::max(0, t2 - 2)] + dp[t1 - 1][std::max(0, t2 - 3)]) / 4.0;

                dp[t2][t1] = (dp[std::max(0, t2 - 4)][t1] + dp[std::max(0, t2 - 3)][t1 - 1] + 
                            dp[std::max(0, t2 - 2)][std::max(0, t1 - 2)] + dp[t2 - 1][std::max(0, t1 - 3)]) / 4.0;
            }

            if (dp[t1][t1] > 1 - 1e-5) {
                return 1.0;
            }
        }

        return dp[m][m];
    }
public:
    double soupServings(int n) {
        return by_iterative_dp(n);
        //return by_recursive_dp(n);
    }
};