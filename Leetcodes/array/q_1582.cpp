/*
Given an m x n binary matrix mat, return the number of special positions in mat.

A position (i, j) is called special if mat[i][j] == 1 and all other elements in row i and column j are 0 (rows and columns are 0-indexed).

 

Example 1:

Input: mat = [[1,0,0],[0,0,1],[1,0,0]]
Output: 1
Explanation: (1, 2) is a special position because mat[1][2] == 1 and all other elements in row 1 and column 2 are 0.

Example 2:

Input: mat = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3
Explanation: (0, 0), (1, 1) and (2, 2) are special positions.

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 100
    mat[i][j] is either 0 or 1.


*/

class Solution {
public:
    int numSpecial(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        std::vector<int> row_1s(rows, 0);
        std::vector<int> col_1s(cols, 0);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 1) {
                    ++row_1s[r];
                    ++col_1s[c];
                }
            }
        }

        int cnt = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (mat[r][c] == 1 && row_1s[r] == 1 && col_1s[c] == 1) {
                    ++cnt;
                }
            }
        }

        return cnt;
    }
};