/*
There is a row of n houses, where each house can be painted one of three colors: red, blue, or green. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by an n x 3 cost matrix costs.

For example, costs[0][0] is the cost of painting house 0 with the color red; costs[1][2] is the cost of painting house 1 with color green, and so on...

Return the minimum cost to paint all houses.

Example 1:

Input: costs = [[17,2,17],[16,16,5],[14,3,19]]
Output: 10
Explanation: Paint house 0 into blue, paint house 1 into green, paint house 2 into blue.
Minimum cost: 2 + 5 + 3 = 10.

Example 2:

Input: costs = [[7,6,2]]
Output: 2

Constraints:

    costs.length == n
    costs[i].length == 3
    1 <= n <= 100
    1 <= costs[i][j] <= 20

*/

class Solution {
private:
    int iterative(vector<vector<int>>& costs) {
        int N = costs.size();

        for (int i = 1; i < N; ++i) {
            costs[i][0] = costs[i][0] + std::min(costs[i - 1][1], costs[i - 1][2]);
            costs[i][1] = costs[i][1] + std::min(costs[i - 1][0], costs[i - 1][2]);
            costs[i][2] = costs[i][2] + std::min(costs[i - 1][1], costs[i - 1][0]);
        }

        return std::min(costs[N - 1][0], std::min(costs[N - 1][1], costs[N - 1][2]));
    }
    int recursive(vector<vector<int>>& costs, int pre, int house, std::vector<std::vector<int>>& mem) {
        if (costs.size() == house) {
            return 0;
        }

        if (pre != -1 && mem[house][pre] != -1) {
            return mem[house][pre];
        }

        int val = 2001;
        for (int c = 0; c < 3; ++c) {
            if (c != pre) {
                val = std::min(val, costs[house][c] + recursive(costs, c, house + 1, mem));
            }
        }

        if (pre != -1) {
            mem[house][pre] = val;
        } else {
            mem[house][0] = val;
        }
        
        return val;
    }
public:
    int minCost(vector<vector<int>>& costs) {
        //std::vector<std::vector<int>> mem(costs.size(), std::vector<int>(3, -1));

        //return recursive(costs, -1, 0, mem);
        return iterative(costs);
    }
};