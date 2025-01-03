/*
Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.

 

Example 1:

Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
Output: 2
Explanation: 
Islands in gray are closed because they are completely surrounded by water (group of 1s).

Example 2:

Input: grid = [[0,0,1,0,0],[0,1,0,1,0],[0,1,1,1,0]]
Output: 1

Example 3:

Input: grid = [[1,1,1,1,1,1,1],
               [1,0,0,0,0,0,1],
               [1,0,1,1,1,0,1],
               [1,0,1,0,1,0,1],
               [1,0,1,1,1,0,1],
               [1,0,0,0,0,0,1],
               [1,1,1,1,1,1,1]]
Output: 2

 

Constraints:

    1 <= grid.length, grid[0].length <= 100
    0 <= grid[i][j] <=1


*/

class Solution {
private:
    int bfs(vector<vector<int>>& grid, int r, int c, std::vector<std::pair<int, int>>& directions) {
        int rows = grid.size();
        int cols = grid[0].size();

        std::queue<std::pair<int, int>> q;
        q.push({r, c});

        //change to 1 to marked as visisted
        grid[r][c] = 1;

        while (!q.empty()) {
            std::pair node = q.front();
            q.pop();

            int currR = node.first;
            int currC = node.second;

            for (const std::pair<int, int>& p : directions) {
                int nextR = currR + p.first;
                int nextC = currC + p.second;

                if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols && grid[nextR][nextC] == 0) {
                    q.push({nextR, nextC});
                    grid[nextR][nextC] = 1;
                }
            }
            
        }

        return 1;
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        //loop through row 0 and last
        for (int c = 0; c < grid[0].size(); ++c) {
            //row 0
            if (grid[0][c] == 0) {
                bfs(grid, 0, c, directions);
            }

            //row last
            if (grid[grid.size() - 1][c] == 0) {
                bfs(grid, grid.size() - 1, c, directions);
            }
        }

        //loop through column 0 and last
        for (int r = 0; r < grid.size(); ++r) {

            if (grid[r][0] == 0) {
                //column 0
                bfs(grid, r, 0, directions);
            }

            if (grid[r][grid[0].size() - 1] == 0) {
                //column last
                bfs(grid, r, grid[0].size() - 1, directions);
            }
        }

        int count = 0;
        //loop through inner cells
        for (int r = 1; r < grid.size() - 1; ++r) {
            for (int c = 1; c < grid[0].size() - 1; ++c) {

                if (grid[r][c] == 0) {
                    count += bfs(grid, r, c, directions);
                }
            }
        }
        
        return count;
    }
};