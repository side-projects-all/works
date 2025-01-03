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
    vector<vector<int>> compress_zero(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int rows1 = mat1.size();
        int cols1 = mat1[0].size();
        int rows2 = mat2.size();
        int cols2 = mat2[0].size();

        std::vector<std::vector<std::pair<int, int>>> c1(rows1);
        std::vector<std::vector<std::pair<int, int>>> c2(rows2);

        //compressed matrix 1
        for (int r = 0; r < rows1; ++r) {
            for (int c = 0; c < cols1; ++c) {
                if (mat1[r][c] != 0) {
                    c1[r].push_back({mat1[r][c], c});
                }
            }
        }

        //compressed matrix 2
        for (int r = 0; r < rows2; ++r) {
            for (int c = 0; c < cols2; ++c) {
                if (mat2[r][c] != 0) {
                    c2[r].push_back({mat2[r][c], c});
                }
            }
        }

        std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));
        for (int r1 = 0; r1 < rows1; ++r1) {
            for (auto [e1, c1] : c1[r1]) {
                for (auto [e2, c2] : c2[c1]) {
                    result[r1][c2] += e1 * e2;
                }
            }
        }

        return result;
    }
    vector<vector<int>> ignore_zero(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int rows1 = mat1.size();
        int cols1 = mat1[0].size();
        int rows2 = mat2.size();
        int cols2 = mat2[0].size();

        std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

        for (int r1 = 0; r1 < rows1; ++r1) {
            for (int c1 = 0; c1 < cols1; ++c1) {

                if (mat1[r1][c1] != 0) {
                    for (int c2 = 0; c2 < cols2; ++c2) {
                        result[r1][c2] += mat1[r1][c1] * mat2[c1][c2];
                    }
                }
            }
        }
        return result;
    }
    vector<vector<int>> naive(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int rows1 = mat1.size();
        int cols1 = mat1[0].size();
        int rows2 = mat2.size();
        int cols2 = mat2[0].size();

        std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2, 0));

        for (int r1 = 0; r1 < rows1; ++r1) {
            for (int c2 = 0; c2 < cols2; ++c2) {
                for (int r2 = 0; r2 < rows2; ++r2) {
                    result[r1][c2] += mat1[r1][r2] * mat2[r2][c2];
                }
            }
        }

        return result;
    }
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        //return naive(mat1, mat2);
        //return ignore_zero(mat1, mat2);
        return compress_zero(mat1, mat2);
    }
};