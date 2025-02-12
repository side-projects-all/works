/*
ou have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.

Train tickets are sold in three different ways:

    a 1-day pass is sold for costs[0] dollars,
    a 7-day pass is sold for costs[1] dollars, and
    a 30-day pass is sold for costs[2] dollars.

The passes allow that many days of consecutive travel.

    For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.

Return the minimum number of dollars you need to travel every day in the given list of days.

 

Example 1:

Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
In total, you spent $11 and covered all the days of your travel.

Example 2:

Input: days = [1,2,3,4,5,6,7,8,9,10,30,31], costs = [2,7,15]
Output: 17
Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
On day 1, you bought a 30-day pass for costs[2] = $15 which covered days 1, 2, ..., 30.
On day 31, you bought a 1-day pass for costs[0] = $2 which covered day 31.
In total, you spent $17 and covered all the days of your travel.

 

Constraints:

    1 <= days.length <= 365
    1 <= days[i] <= 365
    days is in strictly increasing order.
    costs.length == 3
    1 <= costs[i] <= 1000

*/

class Solution {
private:
    int iterative(vector<int>& days, vector<int>& costs) {
        int n = days.size();
        std::vector<int> dp(days[n - 1] + 1);   //min cost
        
        for (int d = 1, i = 0; d <= days[n - 1]; ++d) {

            if (d < days[i]) {
                dp[d] = dp[d - 1];
            } else {
                ++i;

                dp[d] = std::min({dp[d - 1] + costs[0], dp[std::max(0, d - 7)] + costs[1], dp[std::max(0, d - 30)] + costs[2]});
            }
        }

        return dp[days[n - 1]];
    }
    int recursive(vector<int>& days, vector<int>& costs, int currDay, std::vector<bool>& needTravel, 
                                                                        std::vector<int>& mem) {
        if (currDay > days[days.size() - 1]) {
            return 0;
        }

        if (!needTravel[currDay]) {
            return recursive(days, costs, currDay + 1, needTravel, mem);
        }

        if (mem[currDay] != -1) {
            return mem[currDay];
        }

        int one = costs[0] + recursive(days, costs, currDay + 1, needTravel, mem);
        int seven = costs[1] + recursive(days, costs, currDay + 7, needTravel, mem);
        int thirty = costs[2] + recursive(days, costs, currDay + 30, needTravel, mem);

        mem[currDay] = std::min(one, std::min(seven, thirty));
        return mem[currDay];
    }
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        /*
        int n = days.size();
        int maxDay = days[n - 1];
        std::vector<bool> needTravel(maxDay + 1);
        for (int d : days) {
            needTravel[d] = true;
        }

        std::vector<int> mem(maxDay + 1, -1);
        return recursive(days, costs, 1, needTravel, mem);
        */

        return iterative(days, costs);
    }
};