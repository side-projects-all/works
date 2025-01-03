/*
You are given an n x n integer matrix grid.

Generate an integer matrix maxLocal of size (n - 2) x (n - 2) such that:

    maxLocal[i][j] is equal to the largest value of the 3 x 3 matrix in grid centered around row i + 1 and column j + 1.

In other words, we want to find the largest value in every contiguous 3 x 3 matrix in grid.

Return the generated matrix.

 

Example 1:

Input: grid = [[9,9,8,1],[5,6,2,6],[8,2,6,4],[6,2,2,2]]
Output: [[9,9],[8,6]]
Explanation: The diagram above shows the original matrix and the generated matrix.
Notice that each value in the generated matrix corresponds to the largest value of a contiguous 3 x 3 matrix in grid.

Example 2:

Input: grid = [[1,1,1,1,1],[1,1,1,1,1],[1,1,2,1,1],[1,1,1,1,1],[1,1,1,1,1]]
Output: [[2,2,2],[2,2,2],[2,2,2]]
Explanation: Notice that the 2 is contained within every contiguous 3 x 3 matrix in grid.

 

Constraints:

    n == grid.length == grid[i].length
    3 <= n <= 100
    1 <= grid[i][j] <= 100

*/

class Solution {
public:
    vector<vector<int>> largestLocal(vector<vector<int>>& grid) {
        int N = grid.size();
        std::vector<std::vector<int>> ans(N - 2, std::vector<int>(N - 2));

        std::function<int(int, int)> find_max = [&](int row, int col) -> int {
            int M = 0;
            for (int i = row; i < row + 3; ++i) {
                M = std::max(M, *std::max_element(grid[i].begin() + col, grid[i].begin() + col + 3));
            }

            return M;
        };
        
        for (int r = 0; r < N - 2; ++r) {
            for (int c = 0; c < N - 2; ++c) {
                ans[r][c] = find_max(r, c);
            }
        }
        return ans;
    }
};