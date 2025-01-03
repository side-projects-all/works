/*
Given an m x n matrix, return all elements of the matrix in spiral order.

 

Example 1:

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:

Input: matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 10
    -100 <= matrix[i][j] <= 100


*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        std::vector<int> result;

        //my original answer
        /*
        //0: movement of row, 1: movement of column
        //left, (0, -1)
        //right, (0, 1)
        //up, (-1, 0)
        //down (1, 0)
        std::vector<int> direction = { 0, 1 };  //initally

        int total = matrix.size() * matrix[0].size();

        int rows_upperbound = matrix.size();
        int cols_upperbound = matrix[0].size();
        int rows_lowerbound = 0;
        int cols_lowerbound = 0;
        
        int row = 0;
        int col = 0;

        int count =0;
        while (count < total) {
            result.push_back(matrix[row][col]);
            ++count;

            int new_row = row + direction[0];
            int new_col = col + direction[1];

            //because it start from row 0 and column 0 and changes in clock-wise direction, 
            //if we reach the column upperbound, it means we complete lowest row, ++rows_lowerbound, 
            //and if we reach the row upperbound, it means we complete largest column, --cols_upperbound,
            //and if we reach the column lowerbound, it means we complete largest row, --rows_upperbound, 
            //and if we reach the row lowerbound, it means we complete lowest column, ++cols_lowerbound, 
            //then we complete one round!
            
            if (new_col < cols_lowerbound) {
                //move up
                direction[0] = -1;
                direction[1] = 0;
                
                row = row + direction[0];
                col = col + direction[1];

                --rows_upperbound;

            } else if (new_col == cols_upperbound) {
                //move down
                direction[0] = 1;
                direction[1] = 0;

                row = row + direction[0];
                col = col + direction[1];

                ++rows_lowerbound;
                
            } else if (new_row < rows_lowerbound) {
                //move right
                direction[0] = 0;
                direction[1] = 1;

                row = row + direction[0];
                col = col + direction[1];

                ++cols_lowerbound;

            } else if (new_row == rows_upperbound) {
                //move right
                direction[0] = 0;
                direction[1] = -1;

                row = row + direction[0];
                col = col + direction[1];
                
                --cols_upperbound;

            } else {

                row = new_row;
                col = new_col;
            }
        }
        */

        //summarize from above, we just need to move the boundary
        int rows = matrix.size();
        int cols = matrix[0].size();
        
        int up = 0;
        int left = 0;
        int right = cols - 1;
        int down = rows - 1;

        while (result.size() < rows * cols) {
            //traverse from left to right
            for (int col = left; col <= right; ++col) {
                result.push_back(matrix[up][col]);
            }

            for (int row = up + 1; row <= down; ++row) {
                result.push_back(matrix[row][right]);
            }

            if (up != down) {
                for (int col = right - 1; col >= left; --col) {
                    result.push_back(matrix[down][col]);
                }
            }

            if (left != right) {
                for (int row = down - 1; row > up; --row) {
                    result.push_back(matrix[row][left]);
                }
            }

            ++left;
            --right;
            ++up;
            --down;
        }

        return result;
    }
};