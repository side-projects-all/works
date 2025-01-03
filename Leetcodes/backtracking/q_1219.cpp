/*
In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.

Return the maximum amount of gold you can collect under the conditions:

    Every time you are located in a cell you will collect all the gold in that cell.
    From your position, you can walk one step to the left, right, up, or down.
    You can't visit the same cell more than once.
    Never visit a cell with 0 gold.
    You can start and stop collecting gold from any position in the grid that has some gold.

 

Example 1:

Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
Output: 24
Explanation:
[[0,6,0],
 [5,8,7],
 [0,9,0]]
Path to get the maximum gold, 9 -> 8 -> 7.

Example 2:

Input: grid = [[1,0,7],[2,0,6],[3,4,5],[0,3,0],[9,0,20]]
Output: 28
Explanation:
[[1,0,7],
 [2,0,6],
 [3,4,5],
 [0,3,0],
 [9,0,20]]
Path to get the maximum gold, 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 15
    0 <= grid[i][j] <= 100
    There are at most 25 cells containing gold.


*/

class Solution {
private:
    int backtracking(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        //int dirs[4][2]{ {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
        
        int max_val = 0;
        std::function<void(int, int, int)> bk = [&](int r, int c, int val_now) {
            
            /*
            if (c < 0 || c >= cols || r < 0 || r >= rows || grid[r][c] == 0) {
                return;
            }*/

            val_now += grid[r][c];
            int gold_here = grid[r][c];
            grid[r][c] = 0;
            max_val = std::max(max_val, val_now);

            if (r + 1 < rows && grid[r + 1][c] > 0) {
                bk(r + 1, c, val_now);
            }
            if (r - 1 >= 0 && grid[r - 1][c] > 0) {
                bk(r - 1, c, val_now);
            }
            if (c + 1 < cols && grid[r][c + 1] > 0) {
                bk(r, c + 1, val_now);
            }
            if (c - 1 >= 0 && grid[r][c - 1] > 0) {
                bk(r, c - 1, val_now);
            }
            grid[r][c] = gold_here;
    
            /*
            bool up = true;
            bool down = true;
            bool left = true;
            bool right = true;
            if (r - 1 < 0 || grid[r - 1][c] == 0) {
                up = false;
            }
            if (r + 1 >= rows || grid[r + 1][c] == 0) {
                down = false;
            }
            if (c - 1 < 0 || grid[r][c - 1] == 0) {
                left = false;
            }
            if (c + 1  >= cols || grid[r][c + 1] == 0) {
                right = false;
            }
            if (!(up || down || left || right)) {
                max_val = std::max(max_val, val_now + grid[r][c]);
                return;
            }

            for (const auto dir : dirs) {
                
                int next_c = c + dir[0];
                int next_r = r + dir[1];
                if (next_c >= 0 && next_c < cols && next_r >= 0 && next_r < rows && grid[next_r][next_c] > 0) {
                    
                    int gold_here = grid[r][c];
                    grid[r][c] = 0;
                    int next_val = val_now + gold_here;
                    bk(next_r, next_c, next_val);
                    grid[r][c] = gold_here;
                }
            }
            */
            
        };

        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (grid[row][col] > 0) {
                    bk(row, col, 0);
                }
            }
        }

        return max_val;
    }
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        return backtracking(grid);
    }
};