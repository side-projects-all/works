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
private:
    bool binary_search(vector<vector<int>>& matrix, int& target, int b, bool is_vertical) {
        int left = b;
        int right = is_vertical ? matrix[0].size() - 1 : matrix.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (is_vertical) {
                if (matrix[b][mid] == target) {
                    return true;

                } else if (matrix[b][mid] > target) {
                    right = mid - 1;

                } else {
                    left = mid + 1;
                }
            } else {
                if (matrix[mid][b] == target) {
                    return true;

                } else if (matrix[mid][b] > target) {
                    right = mid - 1;

                } else {
                    left = mid + 1;
                }
            }
            
        }

        return false;
    }
    bool by_binary_search(vector<vector<int>>& matrix, int target) {
        /*
        int shorter_diagonal = std::min(matrix.size(), matrix[0].size());
        for (int b = 0; b < shorter_diagonal; ++b) {
            
            bool h = binary_search(matrix, target, b, false);
            bool v = binary_search(matrix, target, b, true);

            if (h || v) {
                return true;
            }
        }
        */

        for (int r = 0; r < matrix.size(); ++r) {
            int left = 0;
            int right = matrix[0].size() - 1;

            while (left <= right) {
                int mid = left + (right - left) / 2;

                if (matrix[r][mid] == target) {
                    return true;

                } else if (matrix[r][mid] > target) {
                    right = mid - 1;

                } else {
                    left = mid + 1;
                }       
            }
        }
        return false;
    }
    bool by_two_ptr(vector<vector<int>>& matrix, int target) {
        int r = matrix.size() - 1;
        int c = 0;

        while (r >= 0 && c < matrix[0].size()) {

            if (matrix[r][c] == target) {
                return true;

            } else if (matrix[r][c] > target) {
                --r;

            } else {

                ++c;
            }
        }

        return false;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (target < matrix[0][0] || target > matrix[matrix.size() - 1][matrix[0].size() - 1]) {
            return false;
        }
        //return by_two_ptr(matrix, target);
        return by_binary_search(matrix, target);
    }
};