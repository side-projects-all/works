/*
Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.

A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.

 

Example 1:

Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
Output: [15]
Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 2:

Input: matrix = [[1,10,4,2],[9,3,8,7],[15,16,17,12]]
Output: [12]
Explanation: 12 is the only lucky number since it is the minimum in its row and the maximum in its column.

Example 3:

Input: matrix = [[7,8],[1,2]]
Output: [7]
Explanation: 7 is the only lucky number since it is the minimum in its row and the maximum in its column.

 

Constraints:

    m == mat.length
    n == mat[i].length
    1 <= n, m <= 50
    1 <= matrix[i][j] <= 10^5.
    All elements in the matrix are distinct.


*/

class Solution {
public:
    vector<int> luckyNumbers (vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<int> min_in_row(rows, INT_MAX);
        std::vector<int> max_in_col(cols, INT_MIN);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                min_in_row[r] = std::min(min_in_row[r], matrix[r][c]);
                max_in_col[c] = std::max(max_in_col[c], matrix[r][c]);
            }
        }

        std::unordered_set<int> tmp(max_in_col.begin(), max_in_col.end());
        std::vector<int> ans;
        for (int i = 0; i < min_in_row.size(); ++i) {

            if (tmp.find(min_in_row[i]) != tmp.end()) {
                ans.push_back(min_in_row[i]);
            }
        }

        return ans;
    }
};