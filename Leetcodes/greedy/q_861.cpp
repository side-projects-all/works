/*
A move consists of choosing any row or column and toggling each value in that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).

Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.

Return the highest possible score after making any number of moves (including zero moves).

 

Example 1:

Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
Output: 39
Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39

Example 2:

Input: grid = [[0]]
Output: 1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 20
    grid[i][j] is either 0 or 1.

*/

class Solution {
private:
    int no_modification(vector<vector<int>>& grid) {
        std::size_t rows = grid.size();
        std::size_t cols = grid[0].size();

        int ans = (1 << (cols - 1)) * rows;

        for (int c = 1; c < cols; ++c) {
            
            int same_bits = 0;
            for (int r = 0; r < rows; ++r) {
                if (grid[r][c] == grid[r][0]) {
                    ++same_bits;
                }
            }

            same_bits = std::max(same_bits, static_cast<int>(rows) - same_bits);
            int col_score = (1 << (cols - c - 1)) * same_bits;
            ans += col_score;
        }

        return ans;
    }
    int in_place_modification(vector<vector<int>>& grid) {
        std::size_t rows = grid.size();
        std::size_t cols = grid[0].size();

        //check first column, if 0, then we flip it
        for (int r = 0; r < rows; ++r) {
            if (grid[r][0] == 0) {
                for (int c = 0; c < cols; ++c) {
                    grid[r][c] = 1 - grid[r][c];
                }
            }
        }

        for (int c = 1; c < cols; ++c) {

            int cnt_ones = 0;
            for (int r = 0; r < rows; ++r) {
                if (grid[r][c]) {
                    ++cnt_ones;
                }
            }

            if (cnt_ones < (rows - cnt_ones)) {
                for (int r = 0; r < rows; ++r) {
                    grid[r][c] = 1 - grid[r][c];
                }
            }
        }

        int ans = 0;
        for (int r = 0; r < rows; ++r) {

            int row_sum = 0;
            for (int c = 0; c < cols; ++c) {
                
                if (grid[r][c]) {
                    row_sum += grid[r][c] << (cols - c - 1);
                }
            }
            ans += row_sum;
        }

        return ans;
    }
public:
    int matrixScore(vector<vector<int>>& grid) {
        //return in_place_modification(grid);
        
        return no_modification(grid);
    }
};