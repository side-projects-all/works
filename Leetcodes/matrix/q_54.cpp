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
        
        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<int> ans(rows * cols);
        int lb = 0;         //left most cell
        int rb = cols - 1;  //right most cell
        int top = 0;        //top cell
        int btm = rows - 1; //bottom cell
        int i = 0;
        while (i < rows * cols) {
            //from left to right
            for (int c = lb; c <= rb; ++c, ++i) 
                ans[i] = matrix[top][c];

            //top to bottom
            for (int r = top + 1; r <= btm; ++r, ++i) 
                ans[i] = matrix[r][rb];

            if (i == rows * cols) return ans;
            
            //from right to left
            for (int c = rb - 1; c >= lb; --c, ++i) 
                ans[i] = matrix[btm][c];
            
            //from bottom to top
            for (int r = btm - 1; r > top; --r, ++i)
                ans[i] = matrix[r][lb];
            
            ++lb;
            --rb;
            ++top;
            --btm;
        }

        return ans;
    }
};