/*
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:

    Integers in each row are sorted in ascending from left to right.
    Integers in each column are sorted in ascending from top to bottom.

 

Example 1:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
Output: true

Example 2:

Input: matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
Output: false

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= n, m <= 300
    -10^9 <= matrix[i][j] <= 10^9
    All the integers in each row are sorted in ascending order.
    All the integers in each column are sorted in ascending order.
    -10^9 <= target <= 10^9


*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //p_target = target;
        //p_matrix = matrix;
        /*
        if (matrix.empty() || matrix.size() == 0) {
            return false;
        }*/

        //return recursive(0, 0, matrix[0].size() - 1, matrix.size() - 1);
        return iterative(matrix, target);
    }

private:
    bool iterative(vector<vector<int>>& matrix, int target) {
        int row = matrix.size() - 1;
        int col = 0;

        while (row >= 0 && col < matrix[0].size()) {
            if (matrix[row][col] > target) {
                --row;
            } else if (matrix[row][col] < target) {
                ++col;
            } else {
                return true;
            }

        }

        return false;
    }

    //recursive way would be memory limit exceeded
    bool recursive(int left, int up, int right, int down) {
        if (left > right || up > down) {
            return false;
        } else if (p_target < p_matrix[up][left] || p_target > p_matrix[down][right]) {
            return false;
        }

        int mid = left + (right - left) / 2;

        int row = up;
        while (row <= down && p_matrix[row][mid] <= p_target) {
            if (p_matrix[row][mid] == p_target) {
                return true;
            }

            ++row;
        }

        return recursive(left, row, mid - 1, down) || recursive(mid + 1, up, right, row - 1);
    }

    int p_target;
    std::vector<std::vector<int>> p_matrix;
};