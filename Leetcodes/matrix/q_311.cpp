/*
Given two sparse matrices mat1 of size m x k and mat2 of size k x n, return the result of mat1 x mat2. You may assume that multiplication is always possible.

 

Example 1:

Input: mat1 = [[1,0,0],[-1,0,3]], mat2 = [[7,0,0],[0,0,0],[0,0,1]]
Output: [[7,0,0],[-7,0,3]]

Example 2:

Input: mat1 = [[0]], mat2 = [[0]]
Output: [[0]]

 

Constraints:

    m == mat1.length
    k == mat1[i].length == mat2.length
    n == mat2[i].length
    1 <= m, n, k <= 100
    -100 <= mat1[i][j], mat2[i][j] <= 100


*/

class Solution {
private:
    vector<vector<int>> compressed_row_col(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int rows1 = mat1.size();
        int cols1 = mat1[0].size();
        int rows2 = mat2.size();
        int cols2 = mat2[0].size();

        std::vector<std::vector<std::pair<int,int>>> m1_no_zero(rows1);
        for (int r = 0; r < rows1; ++r) {
            for (int c = 0; c < cols1; ++c) {
                if (mat1[r][c] != 0) {
                    m1_no_zero[r].push_back({mat1[r][c], c});
                }
            }
        }

        std::vector<std::vector<std::pair<int,int>>> m2_no_zero(rows2);
        for (int r = 0; r < rows2; ++r) {
            for (int c = 0; c < cols2; ++c) {
                if (mat2[r][c] != 0) {
                    m2_no_zero[r].push_back({mat2[r][c], c});
                }
            }
        }

        std::vector<std::vector<int>> ans(rows1, std::vector<int>(cols2));
        for (int r = 0; r < m1_no_zero.size(); ++r) {
            for (int c = 0; c < m1_no_zero[r].size(); ++c) {

                int m2_row = m1_no_zero[r][c].second;
                for (int c2 = 0; c2 < m2_no_zero[m2_row].size(); ++c2) {
                   
                   int col = m2_no_zero[m2_row][c2].second;
                   ans[r][col] += m1_no_zero[r][c].first * m2_no_zero[m2_row][c2].first;
                }
            }
        }
        
        return ans;
    }
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        return compressed_row_col(mat1, mat2);
    }
};