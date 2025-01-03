/*
You are given a 0-indexed m x n binary matrix grid.

A 0-indexed m x n difference matrix diff is created with the following procedure:

    Let the number of ones in the ith row be onesRowi.
    Let the number of ones in the jth column be onesColj.
    Let the number of zeros in the ith row be zerosRowi.
    Let the number of zeros in the jth column be zerosColj.
    diff[i][j] = onesRowi + onesColj - zerosRowi - zerosColj

Return the difference matrix diff.

 

Example 1:

Input: grid = [[0,1,1],[1,0,1],[0,0,1]]
Output: [[0,0,4],[0,0,4],[-2,-2,2]]
Explanation:
- diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
- diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
- diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
- diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 2 + 1 - 1 - 2 = 0 
- diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 2 + 1 - 1 - 2 = 0 
- diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 2 + 3 - 1 - 0 = 4 
- diff[2][0] = onesRow2 + onesCol0 - zerosRow2 - zerosCol0 = 1 + 1 - 2 - 2 = -2
- diff[2][1] = onesRow2 + onesCol1 - zerosRow2 - zerosCol1 = 1 + 1 - 2 - 2 = -2
- diff[2][2] = onesRow2 + onesCol2 - zerosRow2 - zerosCol2 = 1 + 3 - 2 - 0 = 2

Example 2:

Input: grid = [[1,1,1],[1,1,1]]
Output: [[5,5,5],[5,5,5]]
Explanation:
- diff[0][0] = onesRow0 + onesCol0 - zerosRow0 - zerosCol0 = 3 + 2 - 0 - 0 = 5
- diff[0][1] = onesRow0 + onesCol1 - zerosRow0 - zerosCol1 = 3 + 2 - 0 - 0 = 5
- diff[0][2] = onesRow0 + onesCol2 - zerosRow0 - zerosCol2 = 3 + 2 - 0 - 0 = 5
- diff[1][0] = onesRow1 + onesCol0 - zerosRow1 - zerosCol0 = 3 + 2 - 0 - 0 = 5
- diff[1][1] = onesRow1 + onesCol1 - zerosRow1 - zerosCol1 = 3 + 2 - 0 - 0 = 5
- diff[1][2] = onesRow1 + onesCol2 - zerosRow1 - zerosCol2 = 3 + 2 - 0 - 0 = 5

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    grid[i][j] is either 0 or 1.


*/

class Solution {
public:
    vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

        //std::vector<int> rows_0(rows, 0);
        std::vector<int> rows_1(rows, 0);
        //std::vector<int> cols_0(cols, 0);
        std::vector<int> cols_1(cols, 0);

        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                rows_1[r] += grid[r][c];
                cols_1[c] += grid[r][c];

                /*
                if (grid[r][c] == 1) {
                    rows_1[r] += 1;
                } else {
                    rows_0[r] += 1;
                }
                */
            }
        }

        /*
        for (int c = 0; c < grid[0].size(); ++c) {
            for (int r = 0; r < grid.size(); ++r) {
                if (grid[r][c] == 0) {
                    cols_0[c] += 1;
                } else {
                    cols_1[c] += 1;
                }
            }
        }*/

        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                //result[r][c] = rows_1[r] + cols_1[c] - rows_0[r] - cols_0[c];
                result[r][c] = 2 * rows_1[r] + 2 * cols_1[c] - rows - cols;
            }
        }

        return result;
    }
};