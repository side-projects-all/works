/*
Given an m x n integer matrix matrix, if an element is 0, set its entire row and column to 0's.

You must do it in place.

 

Example 1:

Input: matrix = [[1,1,1],[1,0,1],[1,1,1]]
Output: [[1,0,1],[0,0,0],[1,0,1]]

Example 2:

Input: matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
Output: [[0,0,0,0],[0,4,5,0],[0,3,1,0]]

 

Constraints:

    m == matrix.length
    n == matrix[0].length
    1 <= m, n <= 200
    -2^31 <= matrix[i][j] <= 2^31 - 1

*/

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool isFirstColZero = false;

        int rows = matrix.size();
        int cols = matrix[0].size();

        //smart solution
        for (int i = 0; i < rows; ++i) {

            if (matrix[i][0] == 0) {
                isFirstColZero = true;
            }

            for (int c = 1; c < cols; ++c) {
                if (matrix[i][c] == 0) {
                    matrix[0][c] = 0;
                    matrix[i][0] = 0;
                }
            }
        }

        for (int r = 1; r < rows; ++r) {
            for (int c = 1; c < cols; ++c) {

                if (matrix[r][0] == 0 || matrix[0][c] == 0) {
                    matrix[r][c] = 0;
                }
                
            }
        }

        //matrix[0][0] for first row condition, i.e. is zero or not
        if (matrix[0][0] == 0) {
            for (int c = 0; c < cols; ++c) {
                matrix[0][c] = 0;
            }
        }

        //finally, first column
        if (isFirstColZero) {
            for (int r = 0; r < rows; ++r) {
                matrix[r][0] = 0;
            }
        }

        //naive 
        //additional tracking space
        /*
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (!visited[r][c] && matrix[r][c] == 0) {
                    visited[r][c] = true;

                    //set row
                    int col = 0;
                    while (col < cols) {
                        
                        if (matrix[r][col] != 0) {
                            visited[r][col] = true;
                            matrix[r][col] = 0;
                        }
                        
                        ++col;
                    }
                    //set col
                    int row = 0;
                    while (row < rows) {

                        if (matrix[row][c] != 0) {
                            visited[row][c] = true;
                            matrix[row][c] = 0;
                        }
                        
                        ++row;
                    }
                } else {

                    visited[r][c] = true;
                }
            }
        }
        */
    }
};