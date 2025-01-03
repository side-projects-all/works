/*
Given an m x n binary grid grid where each 1 marks the home of one friend, return the minimal total travel distance.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:

Input: grid = [[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 6
Explanation: Given three friends living at (0,0), (0,4), and (2,2).
The point (0,2) is an ideal meeting point, as the total travel distance of 2 + 2 + 2 = 6 is minimal.
So return 6.

Example 2:

Input: grid = [[1,1]]
Output: 1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 200
    grid[i][j] is either 0 or 1.
    There will be at least two friends in the grid.


*/

class Solution {

public:
    int minTotalDistance(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        std::vector<std::pair<int, int>> homes;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    homes.push_back({r, c});
                }
            }
        }

        std::sort(homes.begin(), homes.end());
        
        std::vector<int> row_pos(homes.size());
        std::vector<int> col_pos(homes.size());

        int h_len = homes.size();
        for (int i = 0; i < h_len; ++i) {
            row_pos[i] = homes[i].first;
            col_pos[i] = homes[i].second;
        }

        int median_r = row_pos[h_len / 2];

        std::sort(col_pos.begin(), col_pos.end());

        int median_c = col_pos[h_len / 2];
        
        int minDis = 0;
        for (int i = 0; i < h_len; ++i) {
            minDis += std::abs(homes[i].first - median_r) + std::abs(homes[i].second - median_c);
        }

        return minDis;
    }
};