/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'.
*/

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        
        return bfs(grid);
        //return dfs(grid);
    }
    
private:
    int bfs(vector<vector<char>>& grid) {
        int rows = grid.size();
        
        if (rows == 0) {
            return 0;
        }
        
        int cols = grid[0].size();
        
        int num_islands = 0;
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                    
                    //mark as visited
                    grid[r][c] = '0';
                    std::queue<pair<int, int>> neighbors;
                    neighbors.push({r, c});
                    
                    while(!neighbors.empty()) {
                        auto rc = neighbors.front();
                        neighbors.pop();
                        
                        int row = rc.first;
                        int col = rc.second;
                        //test left
                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            neighbors.push({row - 1, col});
                            grid[row - 1][col] = '0';
                        }
                        //test right
                        if (row + 1 < rows && grid[row + 1][col] == '1') {
                            neighbors.push({row + 1, col});
                            grid[row + 1][col] = '0';
                        }
                        //test bottom
                        if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            neighbors.push({row, col - 1});
                            grid[row][col - 1] = '0';
                        }
                        //test top
                        if (col + 1 < cols && grid[row][col + 1] == '1') {
                            neighbors.push({row, col + 1});
                            grid[row][col + 1] = '0';
                        }
                        
                    }
                    
                }
            }
        }
         
        return num_islands;
    }
    
    int dfs(vector<vector<char>>& grid) {
        int rows = grid.size();
        
        if (rows == 0) {
            return 0;
        }
        
        int cols = grid[0].size();
        
        int num_islands = 0;
        std::vector<pair<int, int>> neighbors;
        int row = 0;
        int col = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++num_islands;
                  
                    //mark as visited
                    grid[r][c] = '0';
                    neighbors.push_back({r, c});
                      
                    while(!neighbors.empty()) {
                        auto top = neighbors.back();
                          
                        row = top.first;
                        col = top.second;
                          
                        if (row - 1 >= 0 && grid[row - 1][col] == '1') {
                            //test left
                            grid[row - 1][col] = '0';
                            neighbors.push_back({row - 1, col});
                        } else if (row + 1 < rows && grid[row + 1][col] == '1') {
                            //test right
                            grid[row + 1][col] = '0';
                            neighbors.push_back({row + 1, col});
                        } else if (col - 1 >= 0 && grid[row][col - 1] == '1') {
                            //test bottom
                            grid[row][col - 1] = '0';
                            neighbors.push_back({row, col - 1});
                        } else if (col + 1 < cols && grid[row][col + 1] == '1') {
                            //test top
                            grid[row][col + 1] = '0';
                            neighbors.push_back({row, col + 1});
                        } else {
                            neighbors.pop_back();
                        }
                    }
                }
            }
        }
        
        return num_islands;
    }
    
    
};

