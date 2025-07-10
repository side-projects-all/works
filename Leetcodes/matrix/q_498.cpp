/*
Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.

 

Example 1:

Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,4,7,5,3,6,8,9]

Example 2:

Input: mat = [[1,2],[3,4]]
Output: [1,2,3,4]

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= m, n <= 10^4
    1 <= m * n <= 10^4
    -10^5 <= mat[i][j] <= 10^5


*/

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();
        //only one row
        if (rows == 1) {
            return mat[0];
        }
        //only one col
        if (cols == 1) {
            std::vector<int> ans(rows);
            for (int r = 0; r < rows; ++r) {
                ans[r] = mat[r][0];
            }

            return ans;
        }

        std::vector<int> ans(rows * cols);
        bool is_up_left = true;
        int r = 0;
        int c = 0;
        int i = 0;
        while (i < rows * cols && r < rows && c < cols) {
            ans[i] = mat[r][c];
            
            if (r == rows - 1 && c == cols - 1) {
                break;
            }

            if (is_up_left) {

                if (r - 1 >= 0 && c + 1 < cols) {
                    --r;
                    ++c;
                } else {
                    is_up_left = !is_up_left;
                    if (c + 1 >= cols) {
                        ++r;

                    } else if (r - 1 < 0) {
                        ++c;
                    }
                }
                
            } else {
                if (c - 1 >= 0 && r + 1 < rows) {
                    --c;
                    ++r;
                } else {
                    is_up_left = !is_up_left;
                    if (r + 1 >= rows) {
                        ++c;

                    } else if (c - 1 < 0) {
                        ++r;
                    }
                }
            }
            
            ++i;
        }

        return ans;
    }
};