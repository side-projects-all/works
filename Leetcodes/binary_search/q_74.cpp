/*
You are given an m x n integer matrix matrix with the following two properties:

    Each row is sorted in non-decreasing order.
    The first integer of each row is greater than the last integer of the previous row.

Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

 

Example 1:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:

Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false

 

Constraints:

    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 100
    -10^4 <= matrix[i][j], target <= 10^4


*/

class Solution {
private:
    bool by_binary_search(vector<vector<int>>& matrix, int& target) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        if (target < matrix[0][0] || target > matrix[rows - 1][cols - 1]) {
            return false;
        }

        if (target == matrix[0][0] || target == matrix[rows - 1][cols - 1]) {
            return true;
        }

        int left = 0;
        int right = rows - 1;
        //search first elements of all rows
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (matrix[mid][0] == target) {
                return true;
            }

            if (matrix[mid][0] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        int row = left - 1 > 0 ? left - 1 : 0;
        left = 0;
        right = matrix[row].size() - 1;
        //search the row found before
        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (matrix[row][mid] == target) {
                return true;
            }

            if (matrix[row][mid] > target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return false;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        return by_binary_search(matrix, target);
    }
};