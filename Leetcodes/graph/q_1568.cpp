/*
You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.

The grid is said to be connected if we have exactly one island, otherwise is said disconnected.

In one day, we are allowed to change any single land cell (1) into a water cell (0).

Return the minimum number of days to disconnect the grid.

 

Example 1:

Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]

Output: 2
Explanation: We need at least 2 days to get a disconnected grid.
Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.

Example 2:

Input: grid = [[1,1]]
Output: 2
Explanation: Grid of full water is also disconnected ([[1,1]] -> [[0,0]]), 0 islands.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 30
    grid[i][j] is either 0 or 1.


*/

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        std::pair<bool, int> arti{ false, 0 };
        int land_cells = 0;
        int is_land_cnt = 0;

        std::vector<std::vector<int>> find_time(rows, std::vector<int>(cols, -1));
        std::vector<std::vector<int>> lowest_reachable(rows, std::vector<int>(cols, -1));
        std::vector<std::vector<int>> parent(rows, std::vector<int>(cols, -1));

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    ++land_cells;

                    if (find_time[r][c] == -1) {
                        find_articulations(grid, find_time, lowest_reachable, parent, r, c, arti);

                        ++is_land_cnt;
                    }
                }
            }
        }

        if (is_land_cnt == 0 || is_land_cnt >= 2) {
            return 0;
        }

        if (land_cells == 1) {
            return 1;
        }

        if (arti.first) {
            return 1;
        }

        return 2;
    }
private:
    const int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

    bool is_valid(const vector<vector<int>>& grid, int r, int c) {
        int rows = grid.size();
        int cols = grid[0].size();

        return r >= 0 && c >= 0 && r < rows && c < cols && grid[r][c] == 1;
    }
    void find_articulations(vector<vector<int>>& grid, 
                                vector<vector<int>>& find_time, 
                                    vector<vector<int>>& lowest_reachable, 
                                        vector<vector<int>>& parent, 
                                            int row, int col, std::pair<bool, int>& arti) {

        int rows = grid.size();
        int cols = grid[0].size();
        find_time[row][col] = arti.second;
        ++arti.second;
        lowest_reachable[row][col] = find_time[row][col];
        int children = 0;

        for (const auto& d : dir) {
            int new_r = row + d[0];
            int new_c = col + d[1];

            if (is_valid(grid, new_r, new_c)) {

                if (find_time[new_r][new_c] == -1) {
                    ++children;

                    parent[new_r][new_c] = row * cols + col;

                    find_articulations(grid, find_time, lowest_reachable, parent, new_r, new_c, arti);

                    lowest_reachable[row][col] = std::min(lowest_reachable[row][col], 
                                                            lowest_reachable[new_r][new_c]);

                    if (lowest_reachable[new_r][new_c] >= find_time[row][col] && parent[row][col] != -1) {
                        arti.first = true;
                    }
                } else if (new_r * cols + new_c != parent[row][col]) {
                    lowest_reachable[row][col] = std::min(lowest_reachable[row][col], 
                                                                find_time[new_r][new_c]);
                }
            }
        }

        if (parent[row][col] == -1 && children > 1) {
            arti.first = true;
        }
    }
};