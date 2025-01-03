/*
You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.

The area of an island is the number of cells with a value 1 in the island.

Return the maximum area of an island in grid. If there is no island, return 0.

 

Example 1:

Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
Output: 6
Explanation: The answer is not 11, because the island must be connected 4-directionally.

Example 2:

Input: grid = [[0,0,0,0,0,0,0,0]]
Output: 0

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0 or 1.


*/

class Solution {
private:
    int bfs(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int max = 0;
        std::pair<int, int> directions[4] { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::queue<std::pair<int, int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                
                int count = 0;
                if (grid[r][c] == 1) {
                    
                    grid[r][c] = 0;
                    q.push({r, c});

                    while (!q.empty()) {
                        std::pair<int, int> node = q.front();
                        q.pop();

                        int currR = node.first;
                        int currC = node.second;
                        ++count;

                        for (const std::pair<int, int>& p : directions) {
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

                    max = std::max(max, count);
                }
            }
        }

        return max;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        return bfs(grid);
    }
};