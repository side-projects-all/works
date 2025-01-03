/*
You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.

An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.

Return the number of islands in grid2 that are considered sub-islands.

 

Example 1:

Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
Output: 3
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.

Example 2:

Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]], grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
Output: 2 
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are two sub-islands.

 

Constraints:

    m == grid1.length == grid2.length
    n == grid1[i].length == grid2[i].length
    1 <= m, n <= 500
    grid1[i][j] and grid2[i][j] are either 0 or 1.


*/

class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        rows = grid1.size();
        cols = grid1[0].size();

        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

        int cnt = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (!visited[r][c] && is_land(r, c, grid2) && is_sub(r, c, grid1, grid2, visited)) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }
private:
    int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
    int rows;
    int cols;
    bool is_land(int r, int c, vector<vector<int>>& grid) {
        return grid[r][c] == 1;
    }

    bool is_sub(int r, int c, vector<vector<int>>& grid1, 
                vector<vector<int>>& grid2, vector<vector<bool>>& visited) {
        
        std::queue<std::pair<int, int>> q;
        q.push({r, c});
        visited[r][c] = true;
        bool is_subland = true;

        while (!q.empty()) {
            auto [curr_r, curr_c] = q.front();
            q.pop();

            if (!is_land(curr_r, curr_c, grid1)) {
                is_subland = false;
            }

            for (auto& d : dir) {
                int next_r = curr_r + d[0];
                int next_c = curr_c + d[1];

                if (next_r >= 0 && next_c >= 0 && next_r < rows && next_c < cols && 
                            !visited[next_r][next_c] && is_land(next_r, next_c, grid2)) {

                    q.push({next_r, next_c});
                    visited[next_r][next_c] = true;
                }
                
            }
        }

        return is_subland;
    }

};