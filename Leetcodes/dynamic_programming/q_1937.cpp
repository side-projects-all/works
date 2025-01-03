/*
You are given an m x n integer matrix points (0-indexed). Starting with 0 points, you want to maximize the number of points you can get from the matrix.

To gain points, you must pick one cell in each row. Picking the cell at coordinates (r, c) will add points[r][c] to your score.

However, you will lose points if you pick a cell too far from the cell that you picked in the previous row. For every two adjacent rows r and r + 1 (where 0 <= r < m - 1), picking cells at coordinates (r, c1) and (r + 1, c2) will subtract abs(c1 - c2) from your score.

Return the maximum number of points you can achieve.

abs(x) is defined as:

    x for x >= 0.
    -x for x < 0.

 

Example 1:

Input: points = [[1,2,3],[1,5,1],[3,1,1]]
Output: 9
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 2), (1, 1), and (2, 0).
You add 3 + 5 + 3 = 11 to your score.
However, you must subtract abs(2 - 1) + abs(1 - 0) = 2 from your score.
Your final score is 11 - 2 = 9.

Example 2:

Input: points = [[1,5],[2,3],[4,2]]
Output: 11
Explanation:
The blue cells denote the optimal cells to pick, which have coordinates (0, 1), (1, 1), and (2, 0).
You add 5 + 3 + 4 = 12 to your score.
However, you must subtract abs(1 - 1) + abs(1 - 0) = 1 from your score.
Your final score is 12 - 1 = 11.

 

Constraints:

    m == points.length
    n == points[r].length
    1 <= m, n <= 10^5
    1 <= m * n <= 10^5
    0 <= points[r][c] <= 10^5


*/

class Solution {
public:
    long long maxPoints(vector<vector<int>>& points) {
        int rows = points.size();
        int cols = points[0].size();

        std::vector<long long> prev_row(cols);
        for (int c = 0; c < cols; ++c) {
            prev_row[c] = points[0][c];
        }

        for (int r = 0; r < rows - 1; ++r) {
            std::vector<long long> left_max(cols);
            std::vector<long long> right_max(cols);
            std::vector<long long> curr(cols);

            left_max[0] = prev_row[0];
            for (int c = 1; c < cols; ++c) {
                left_max[c] = std::max(left_max[c - 1] - 1, prev_row[c]);
            }

            right_max[cols - 1] = prev_row[cols - 1];
            for (int c = cols - 2; c >= 0; --c) {
                right_max[c] = std::max(right_max[c + 1] - 1, prev_row[c]);
            }

            for (int c = 0; c < cols; ++c) {
                curr[c] = points[r + 1][c] + std::max(left_max[c], right_max[c]);
            }

            prev_row = curr;
        }

        /*
        long long max_pnts = 0;
        for (int c = 0; c < cols; ++c) {
            max_pnts = std::max(max_pnts, prev_row[c]);
        }
        return max_pnts;
        */

        return *std::max_element(prev_row.begin(), prev_row.end());
    }
};