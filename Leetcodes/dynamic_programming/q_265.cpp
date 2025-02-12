/*
There are a row of n houses, each house can be painted with one of the k colors. The cost of painting each house with a certain color is different. You have to paint all the houses such that no two adjacent houses have the same color.

The cost of painting each house with a certain color is represented by an n x k cost matrix costs.

    For example, costs[0][0] is the cost of painting house 0 with color 0; costs[1][2] is the cost of painting house 1 with color 2, and so on...

Return the minimum cost to paint all houses.

 

Example 1:

Input: costs = [[1,5,3],[2,9,4]]
Output: 5
Explanation:
Paint house 0 into color 0, paint house 1 into color 2. Minimum cost: 1 + 4 = 5; 
Or paint house 0 into color 2, paint house 1 into color 0. Minimum cost: 3 + 2 = 5.

Example 2:

Input: costs = [[1,3],[2,4]]
Output: 5

 

Constraints:

    costs.length == n
    costs[i].length == k
    1 <= n <= 100
    2 <= k <= 20
    1 <= costs[i][j] <= 20

*/

class Solution {
private:
    int iterative(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();
        for (int i = 1; i < n; ++i) {

            int min01 = -1;
            int min02 = -1;
            for (int j = 0; j < k; ++j) {
                int cost = costs[i - 1][j];

                if (min01 == -1 || cost < costs[i - 1][min01]) {
                    min02 = min01;
                    min01 = j;

                } else if (min02 == -1 || cost < costs[i - 1][min02]) {
                    min02 = j;
                }
            }

            for (int j = 0; j < k; ++j) {
                if (j == min01) {
                    costs[i][j] += costs[i - 1][min02];
                } else {
                    costs[i][j] += costs[i - 1][min01];
                }
            }
        }

        return *std::min_element(costs[n - 1].begin(), costs[n - 1].end());
    }
    int recursive(vector<vector<int>>& costs, int rowNow, int lastCol, std::vector<std::vector<int>>& mem) {
            if (rowNow == costs.size()) {
                return 0;
            }

            if (lastCol != -1 && mem[rowNow][lastCol] != -1) {
                return mem[rowNow][lastCol];
            }

            int val = 20 * costs.size() + 1;
            for (int c = 0; c < costs[rowNow].size(); ++c) {
                if (c != lastCol) {
                    if (costs[rowNow][c] < val) {
                        val = std::min(val, costs[rowNow][c] + recursive(costs, rowNow + 1, c, mem));
                    }
                   
                }
            }

            if (lastCol != -1) {
                mem[rowNow][lastCol] = val;
            } else {
                mem[rowNow][0] = val;
            }
            
            return val;
        }
public:
    int minCostII(vector<vector<int>>& costs) {
        //std::vector<std::vector<int>> mem(costs.size(), std::vector<int>(costs[0].size(), -1));
        //return recursive(costs, 0, -1, mem);

        return iterative(costs);
    }
};class Solution {
private:
    int iterative(vector<vector<int>>& costs) {

        for (int r = costs.size() - 2; r >= 0; --r) {
            for (int c = 0; c < costs[r].size(); ++c) {
                int val = 20 * 100 + 1;

                for (int i = 0; i < costs[r].size(); ++i) {
                    if (i != c) {
                        val = std::min(val, costs[r][c] + costs[r + 1][i]);
                    }
                }

                costs[r][c] = val;
            }
        }

        int min = 20 * 100 + 1;
        for (int i = 0; i < costs[0].size(); ++i) {
            min = std::min(min, costs[0][i]);
        }

        return min;
    }
    int recursive(vector<vector<int>>& costs, int rowNow, int lastCol, std::vector<std::vector<int>>& mem) {
            if (rowNow == costs.size()) {
                return 0;
            }

            if (lastCol != -1 && mem[rowNow][lastCol] != -1) {
                return mem[rowNow][lastCol];
            }

            int val = 20 * costs.size() + 1;
            for (int c = 0; c < costs[rowNow].size(); ++c) {
                if (c != lastCol) {
                    if (costs[rowNow][c] < val) {
                        val = std::min(val, costs[rowNow][c] + recursive(costs, rowNow + 1, c, mem));
                    }
                   
                }
            }

            if (lastCol != -1) {
                mem[rowNow][lastCol] = val;
            } else {
                mem[rowNow][0] = val;
            }
            
            return val;
        }
public:
    int minCostII(vector<vector<int>>& costs) {
        //std::vector<std::vector<int>> mem(costs.size(), std::vector<int>(costs[0].size(), -1));
        //return recursive(costs, 0, -1, mem);

        return iterative(costs);
    }
};