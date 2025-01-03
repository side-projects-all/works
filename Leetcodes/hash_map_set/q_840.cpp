/*
A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.

Given a row x col grid of integers, how many 3 x 3 contiguous magic square subgrids are there?

Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up to 15.

 

Example 1:

Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
Output: 1
Explanation: 
The following subgrid is a 3 x 3 magic square:

while this one is not:

In total, there is only one magic square inside the given grid.

Example 2:

Input: grid = [[8]]
Output: 0

 

Constraints:

    row == grid.length
    col == grid[i].length
    1 <= row, col <= 10
    0 <= grid[i][j] <= 15


*/

class Solution {

public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int ans = 0;

        for (int r = 0; r + 2 < grid.size(); ++r) {
            for (int c = 0; c + 2 < grid[0].size(); ++c) {
                if (is_magic_square(grid, r, c)) {
                    ++ans;
                }
            }
        }
        return ans;
    }
private:
    bool is_magic_square(vector<vector<int>>& grid, int row, int col) {
        std::string seq = "2943816729438167";
        std::string rev_seq = "7618349276183492";

        std::string border = "";
        std::vector<int> border_indices = { 0, 1, 2, 5, 8, 7, 6, 3 };
        for (int i : border_indices) {
            int n = grid[row + i / 3][col + (i % 3)];
            border += std::to_string(n);
        }

        //first corner is even, middle is five, and find in the sequence
        return (grid[row][col] % 2 == 0 && grid[row + 1][col + 1] == 5 && 
                (seq.find(border) != std::string::npos || rev_seq.find(border) != std::string::npos));
    }
};