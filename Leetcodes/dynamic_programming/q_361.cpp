/*
Given an m x n matrix grid where each cell is either a wall 'W', an enemy 'E' or empty '0', return the maximum enemies you can kill using one bomb. You can only place the bomb in an empty cell.

The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since it is too strong to be destroyed.

 

Example 1:

Input: grid = [["0","E","0","0"],["E","0","W","E"],["0","E","0","0"]]
Output: 3

Example 2:

Input: grid = [["W","W","W"],["0","0","0"],["E","E","E"]]
Output: 1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 500
    grid[i][j] is either 'W', 'E', or '0'.


*/

class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        int ans = 0;
        int row_hits = 0;
        std::vector<int> col_hits(cols);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                
                if (c == 0 || grid[r][c - 1] == 'W') {
                    row_hits = 0;
                    for (int k = c; k < cols; ++k) {
                        if (grid[r][k] == 'W') {
                            break;
                        } else if (grid[r][k] == 'E') {
                            row_hits += 1;
                        }
                    }
                }

                if (r == 0 || grid[r - 1][c] == 'W') {
                    col_hits[c] = 0;
                    for (int k = r; k < rows; ++k) {
                        if (grid[k][c] == 'W') {
                            break;
                        } else if (grid[k][c] == 'E') {
                            col_hits[c] += 1;
                        }
                    }
                }

                if (grid[r][c] == '0') {
                    ans = std::max(ans, row_hits + col_hits[c]);
                }
            }
        }

        return ans;
    }
};