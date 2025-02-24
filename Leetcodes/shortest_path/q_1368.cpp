/*
Given an m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:

    1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
    2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
    3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
    4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])

Notice that there could be some signs on the cells of the grid that point outside the grid.

You will initially start at the upper left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path does not have to be the shortest.

You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.

 

Example 1:

Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
The total cost = 3.

Example 2:

Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).

Example 3:

Input: grid = [[1,2],[4,3]]
Output: 1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    1 <= grid[i][j] <= 4


*/

class Solution {
private:
    int by_zero_one_bfs(vector<vector<int>>& grid) {
        //important detail for following usage!
        //right, left, down, up == 1, 2, 3, 4
        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        int rows = grid.size();
        int cols = grid[0].size();

        deque<std::pair<int, int>> dq;
        dq.push_front({0, 0});

        std::vector<std::vector<int>> min_cost(rows, std::vector<int>(cols, INT_MAX));
        min_cost[0][0] = 0;

        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();

            for (int d = 0; d < 4; ++d) {
                int new_r = r + dirs[d][0];
                int new_c = c + dirs[d][1];
                int cost = (grid[r][c] != d + 1) ? 1 : 0;

                if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols && 
                    min_cost[r][c] + cost < min_cost[new_r][new_c]) {

                    min_cost[new_r][new_c] = min_cost[r][c] + cost;

                    if (cost == 1) {
                        dq.push_back({new_r, new_c});
                    } else {
                        dq.push_front({new_r, new_c});
                    }
                    
                }
            }
        }

        return min_cost[rows - 1][cols - 1];
    }
    int by_dijkstra_alg(vector<vector<int>>& grid) {

        //important detail for following usage!
        //right, left, down, up == 1, 2, 3, 4
        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        int rows = grid.size();
        int cols = grid[0].size();

        auto comp = [](const std::array<int, 3>& a1, const std::array<int, 3>& a2) {
            return a1[0] > a2[0];
        };

        std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, decltype(comp)> pq;

        pq.push({0, 0, 0});

        std::vector<std::vector<int>> min_cost(rows, std::vector<int>(cols, INT_MAX));
        min_cost[0][0] = 0;

        while (!pq.empty()) {
            auto [cost, r, c] = pq.top();
            pq.pop();

            if (min_cost[r][c] != cost) {
                continue;
            }

            //detail at this d
            for (int d = 0; d < 4; ++d) {
                int new_r = r + dirs[d][0];
                int new_c = c + dirs[d][1];

                if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols) {
                    //detail at grid[r][c] - 1 to check if meet the direction
                    int new_cost = cost + (d != (grid[r][c] - 1) ? 1 : 0);

                    if (min_cost[new_r][new_c] > new_cost) {
                        min_cost[new_r][new_c] = new_cost;
                        pq.push({new_cost, new_r, new_c});
                    }
                }
            }
        }

        return min_cost[rows - 1][cols - 1];
    }
    int by_iterative_dp(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<int>> min_changes(rows, std::vector<int>(cols, INT_MAX));
        min_changes[0][0] = 0;

        while (1) {
            std::vector<std::vector<int>> prev_state = min_changes;

            //check from left and top
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (r > 0) {
                        //top
                        min_changes[r][c] = std::min(min_changes[r][c], min_changes[r - 1][c] + (grid[r - 1][c] == 3 ? 0 : 1));
                    }

                    if (c > 0) {
                        //left
                        min_changes[r][c] = std::min(min_changes[r][c], min_changes[r][c - 1] + (grid[r][c - 1] == 1 ? 0 : 1));
                    }
                }
            }

            //check from right and bottom
            for (int r = rows - 1; r >= 0 ; --r) {
                for (int c = cols - 1; c >= 0; --c) {
                    if (r < rows - 1) {
                        //bottom
                        min_changes[r][c] = std::min(min_changes[r][c], min_changes[r + 1][c] + (grid[r + 1][c] == 4 ? 0 : 1));
                    }

                    if (c < cols - 1) {
                        //right
                        min_changes[r][c] = std::min(min_changes[r][c], min_changes[r][c + 1] + (grid[r][c + 1] == 2 ? 0 : 1));
                    }
                }
            }

            if (min_changes == prev_state) {
                break;
            }
        }

        return min_changes[rows - 1][cols - 1];
    }
public:
    int minCost(vector<vector<int>>& grid) {
        //return by_iterative_dp(grid);
        //return by_dijkstra_alg(grid);
        return by_zero_one_bfs(grid);
    }
};