/*
You are given an m x n integer matrix grid containing distinct positive integers.

You have to replace each integer in the matrix with a positive integer satisfying the following conditions:

    The relative order of every two elements that are in the same row or column should stay the same after the replacements.
    The maximum number in the matrix after the replacements should be as small as possible.

The relative order stays the same if for all pairs of elements in the original matrix such that grid[r1][c1] > grid[r2][c2] where either r1 == r2 or c1 == c2, then it must be true that grid[r1][c1] > grid[r2][c2] after the replacements.

For example, if grid = [[2, 4, 5], [7, 3, 9]] then a good replacement could be either grid = [[1, 2, 3], [2, 1, 4]] or grid = [[1, 2, 3], [3, 1, 4]].

Return the resulting matrix. If there are multiple answers, return any of them.

 

Example 1:

Input: grid = [[3,1],[2,5]]
Output: [[2,1],[1,2]]
Explanation: The above diagram shows a valid replacement.
The maximum number in the matrix is 2. It can be shown that no smaller value can be obtained.

Example 2:

Input: grid = [[10]]
Output: [[1]]
Explanation: We replace the only number in the matrix with 1.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 1000
    1 <= m * n <= 10^5
    1 <= grid[i][j] <= 10^9
    grid consists of distinct integers.


*/

class Solution {
public:
    vector<vector<int>> minScore(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();

        // Create a vector nums that stores the values of the matrix and their
        // indices.
        std::vector<std::tuple<int, int, int>> nums;

        // Create rows and cols to store the minimum values for every row and
        // column.
        std::vector<int> rows(row, 1);
        std::vector<int> cols(col, 1);

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                nums.push_back(std::make_tuple(grid[i][j], i, j));
            }
        }
        std::sort(nums.begin(), nums.end());

        for (auto& tup : nums) {
            
            auto [val, x, y] = tup;
            
            // Find the maximum value of rows[x] and cols[y] till now and assign
            // it to val.
            val = std::max(rows[x], cols[y]);
            grid[x][y] = val;
            // Update the new maximum value in rows[x] and cols[y].
            rows[x] = cols[y] = val + 1;
        }
        return grid;
    }
};