/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

An island is considered to be the same as another if and only if one island can be translated (and not rotated or reflected) to equal the other.

Return the number of distinct islands.

 

Example 1:

Input: grid = [[1,1,0,0,0],[1,1,0,0,0],[0,0,0,1,1],[0,0,0,1,1]]
Output: 1

Example 2:

Input: grid = [[1,1,0,1,1],[1,0,0,0,0],[0,0,0,0,1],[1,1,0,1,1]]
Output: 3

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0 or 1.


*/

class Solution {
private:
    void dfs(vector<vector<int>>& grid, int rows, int cols, int r, int c, char dir, 
                        std::string& currIsland, std::vector<std::vector<bool>>& visited) {

        if (r < 0 || c < 0 || r >= rows || c >= cols) {
            return;
        }

        if (visited[r][c] || grid[r][c] == 0) {
            return;
        }

        visited[r][c] = true;
        currIsland += dir;
        dfs(grid, rows, cols, r + 1, c, 'D', currIsland, visited);
        dfs(grid, rows, cols, r - 1, c, 'U', currIsland, visited);
        dfs(grid, rows, cols, r, c + 1, 'R', currIsland, visited);
        dfs(grid, rows, cols, r, c - 1, 'L', currIsland, visited);

        //to prevent different shape but the same path because of backtracking
        currIsland += '0';
    }
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
        std::unordered_set<std::string> islands;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                std::string currIsland = "";
                dfs(grid, rows, cols, r, c, '0', currIsland, visited);

                if (currIsland.size() == 0) {
                    continue;
                }

                islands.insert(currIsland);
            }
        }

        return islands.size();
    }
};