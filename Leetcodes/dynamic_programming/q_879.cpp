/*
There is a group of n members, and a list of various crimes they could commit. The ith crime generates a profit[i] and requires group[i] members to participate in it. If a member participates in one crime, that member can't participate in another crime.

Let's call a profitable scheme any subset of these crimes that generates at least minProfit profit, and the total number of members participating in that subset of crimes is at most n.

Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo 109 + 7.

 

Example 1:

Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
Output: 2
Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
In total, there are 2 schemes.

Example 2:

Input: n = 10, minProfit = 5, group = [2,3,5], profit = [6,7,8]
Output: 7
Explanation: To make a profit of at least 5, the group could commit any crimes, as long as they commit one.
There are 7 possible schemes: (0), (1), (2), (0,1), (0,2), (1,2), and (0,1,2).

 

Constraints:

    1 <= n <= 100
    0 <= minProfit <= 100
    1 <= group.length <= 100
    1 <= group[i] <= 100
    profit.length == group.length
    0 <= profit[i] <= 100


*/

class Solution {
private:
    int recursive(int n, int minProfit, vector<int>& groups, vector<int>& profits) {
        int mod = 1000000007;
        int mem[101][101][101]; //because of the constraints: 1 <= n <= 100
        memset(mem, -1, sizeof(mem));

        std::function<int(int, int, int)> recurr = [&](int i, int used_guys, int profit_now) -> int {
            //base case
            if (i == groups.size()) {
                return profit_now >= minProfit;
            }

            if (mem[i][used_guys][profit_now] != -1) {
                return mem[i][used_guys][profit_now];
            }

            //not use this group
            int ans = recurr(i + 1, used_guys, profit_now);
            if (used_guys + groups[i] <= n) {
                //we only care about if profit_now is larger or equal to minProfit.
                //using minProfit to replace could fit our memoization space limit!!
                ans += recurr(i + 1, used_guys + groups[i], std::min(minProfit, profit_now + profits[i]));
            }

            return mem[i][used_guys][profit_now] = ans % mod;
        };

        return recurr(0, 0, 0);
    }
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        return recursive(n, minProfit, group, profit);
    }
};