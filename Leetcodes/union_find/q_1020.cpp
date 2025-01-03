/*
You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.

A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.

Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.

 

Example 1:

Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
Output: 3
Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.

Example 2:

Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 0
Explanation: All 1s are either on the boundary or can reach the boundary.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 500
    grid[i][j] is either 0 or 1.


*/

class Solution {
private:
    int bfs(vector<vector<int>>& grid) {

        int rows = grid.size();
        int cols = grid[0].size();

        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        int totalCounts = 0;
        std::queue<std::pair<int, int>> q;
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                
                if (grid[r][c] == 1)  {
                    int counts = 0;
                    bool hasBoundaryCell = false;
                    
                    q.push({r, c});
                    grid[r][c] = 0;
                    
                    while (!q.empty()) {

                        std::pair<int, int> node = q.front();
                        q.pop();

                        int currR = node.first;
                        int currC = node.second;

                        if (!hasBoundaryCell && 
                                (currR == 0 || currR == rows - 1 || currC == 0 || currC == cols - 1)) {
                            
                            hasBoundaryCell = true;
                            
                        } else {
                            ++counts;
                        }
                        
                        //check if the cell were nearby boundary
                        for (const auto& p : directions) {
                            int nextR = currR + p.first;
                            int nextC = currC + p.second;

                            if (nextR >= 0 && nextR < rows && 
                                    nextC >= 0 && nextC < cols && 
                                            grid[nextR][nextC] == 1) {

                                q.push({nextR, nextC});
                                grid[nextR][nextC] = 0;

                            }
                        }
                    }

                    if (!hasBoundaryCell) {
                        totalCounts += counts;
                    }
                }
            }
        }

        return totalCounts;
    }

public:
    int numEnclaves(vector<vector<int>>& grid) {
        return bfs(grid);
    }
};