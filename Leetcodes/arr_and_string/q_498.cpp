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
        std::vector<int> result;

        //edge case
        if (mat.size() == 1 && mat[0].size() == 1) {
            return { mat[0][0] };
        }

        //only 1 row
        if (mat.size() == 1) {
            return mat[0];
        }

        //only 1 col
        if (mat[0].size() == 1) { 
            
            for (int i = 0; i < mat.size(); ++i) {
                result.push_back(mat[i][0]);
            }

            return result;
        }

        //my initial solution
        /*
        int len = mat.size() + mat[0].size();
        std::vector<std::vector<int>> tmp(len, std::vector<int>());

        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if ((i+ j) % 2 == 0) {
                    tmp[(i+ j)].insert(tmp[(i+ j)].begin(), mat[i][j]);
                } else {
                    tmp[(i+ j)].push_back(mat[i][j]);
                }
            }
        }

        for (int i = 0; i < tmp.size(); ++i) {
            for (int j = 0; j < tmp[i].size(); ++j) {
                result.push_back(tmp[i][j]);
            }
        }

        return result;
        */

        //find all start points from first row and last column, and loop through them
        //the only difference is odd columns need to be reversed
        /*
        int rows =  mat.size();
        int cols = mat[0].size();
        int total =  rows * cols;        

        std::vector<int> tmp;
        for (int d = 0; d < total - 1; ++d) {
            tmp.clear();

            int r = (d < cols) ? 0 : d - cols + 1;
            int c = (d < cols) ? d : cols - 1;

            while (r < rows && c > -1) {
                tmp.push_back(mat[r][c]);
                ++r;
                --c;
            }

            if (d % 2 == 0) {
                std::reverse(tmp.begin(), tmp.end());
            }

            for (int i = 0; i < tmp.size(); ++i) {
                result.push_back(tmp[i]);
                
            }
        }
        */

        //by simulation way
        int rows =  mat.size();
        int cols = mat[0].size();
        bool goUp = true;

        int row = 0;
        int col = 0;

        while (row < rows && col < cols) {
            result.push_back(mat[row][col]);

            int new_row = row + ((goUp == true) ? -1 : 1);
            int new_col = col + ((goUp == true) ? 1 : -1);

            if (new_row < 0 || new_row == rows || new_col < 0 || new_col == cols) {
                
                //handling the reach boundary situations
                if (goUp) {
                    row += ((col == (cols - 1)) ? 1 : 0);
                    col += ((col < (cols - 1)) ? 1 : 0);

                } else {
                    
                    col += ((row == (rows - 1)) ? 1 : 0);
                    row += ((row < (rows - 1)) ? 1 : 0);
                }
                
                goUp = !goUp;   //reverse this sentinel
            } else {
                row = new_row;
                col = new_col;
            }   
        }

        return result;
    }
};