/*
You have some coins.  The i-th coin has a probability prob[i] of facing heads when tossed.

Return the probability that the number of coins facing heads equals target if you toss every coin exactly once.

 

Example 1:

Input: prob = [0.4], target = 1
Output: 0.40000

Example 2:

Input: prob = [0.5,0.5,0.5,0.5,0.5], target = 0
Output: 0.03125

 

Constraints:

    1 <= prob.length <= 1000
    0 <= prob[i] <= 1
    0 <= target <= prob.length
    Answers will be accepted as correct if they are within 10^-5 of the correct answer.


*/

class Solution {
private:
    double iterative(vector<double>& prob, int target) {
        int n = prob.size();
        std::vector<std::vector<double>> mem(n + 1, std::vector<double>(target + 1, 0.0));

        mem[0][0] = 1.0;
        for (int i = 1; i <= n; ++i) {
            //mem[i][0] means probability of not getting head
            mem[i][0] = mem[i - 1][0] * (1 - prob[i - 1]);

            for (int t = 1; t <= target && t <= i; ++t) {
                //pre-accumulated head * probability of head[i] + 
                //pre-accumulated head * probability of tail[i]
                mem[i][t] = mem[i - 1][t - 1] * prob[i - 1] + mem[i - 1][t] * (1 - prob[i - 1]);
            }
        }

        return mem[n][target];
    }

    double recursive(vector<double>& prob, int target) {
        int n = prob.size();
        std::vector<std::vector<double>> mem(n, std::vector<double>(target + 1, -1));

        //t means residual target, i menas index now
        std::function<double(int, int)> recurr = [&](int i, int t) -> double {
            if (t < 0) {
                return 0;
            }

            if (i == n) {
                return (t == 0 ? 1 : 0);
            }

            if (mem[i][t] != -1) {
                return mem[i][t];
            }

            mem[i][t] = recurr(i + 1, t - 1) * prob[i] + recurr(i + 1, t) * (1 - prob[i]);

            return mem[i][t];
        };

        return recurr(0, target);
    }
public:
    double probabilityOfHeads(vector<double>& prob, int target) {
        //return recursive(prob, target);
        return iterative(prob, target);
    }
};