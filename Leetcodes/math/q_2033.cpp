/*
You are given a 2D integer grid of size m x n and an integer x. In one operation, you can add x to or subtract x from any element in the grid.

A uni-value grid is a grid where all the elements of it are equal.

Return the minimum number of operations to make the grid uni-value. If it is not possible, return -1.

 

Example 1:

Input: grid = [[2,4],[6,8]], x = 2
Output: 4
Explanation: We can make every element equal to 4 by doing the following: 
- Add x to 2 once.
- Subtract x from 6 once.
- Subtract x from 8 twice.
A total of 4 operations were used.

Example 2:

Input: grid = [[1,5],[2,3]], x = 1
Output: 5
Explanation: We can make every element equal to 3.

Example 3:

Input: grid = [[1,2],[3,4]], x = 2
Output: -1
Explanation: It is impossible to make every element equal.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    1 <= x, grid[i][j] <= 10^4


*/

class Solution {
private:
    int by_median(vector<vector<int>>& grid, int& x) {
        int rows = grid.size();
        int cols = grid[0].size();
        std::vector<int> all(rows * cols);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                all[r * cols + c] = grid[r][c];
            }
        }

        std:sort(all.begin(), all.end());
        int med = all[all.size() / 2];
        int med_mod = med % x;

        int ans = 0;
        for (int i = 0; i < all.size(); ++i) {

            if (all[i] % x != med_mod) {
                return -1;
            }

            ans += std::abs(all[i] - med) / x;
        }

        return ans;
    }
public:
    int minOperations(vector<vector<int>>& grid, int x) {
        return by_median(grid, x);
    }
};