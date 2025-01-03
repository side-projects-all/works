/*
You are given an m x n grid where each cell can have one of three values:

    0 representing an empty cell,
    1 representing a fresh orange, or
    2 representing a rotten orange.

Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:

Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4

Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.

Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 10
    grid[i][j] is 0, 1, or 2.


*/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        std::queue<std::pair<int, int>> q;
        int freshOrgs = 0;
        int ROWS = grid.size();
        int COLS = grid[0].size();
        int rotten = 0;

        for (int r = 0; r < ROWS; ++r) {
            for (int c = 0; c < COLS; ++c) {
                if (grid[r][c] == 2) {
                    q.push(std::make_pair(r,c));
                    ++rotten;
                } else if (grid[r][c] == 1) {
                    ++freshOrgs;
                }
            }
        }

        if ((freshOrgs == 0 && q.empty()) || (freshOrgs == 0 && rotten > 0)) {
            return 0;
        }

        int minsElapsed = -1;
        std::vector<std::vector<int>> directions{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int len = q.size();
        while (!q.empty()) {
            
            int levelLen = 0;
            for (int j = 0; j < len; ++j) {
                std::pair<int, int> now = q.front();
                int row = now.first;
                int col = now.second;
                q.pop();

                for (int i = 0; i < directions.size(); ++i) {
                    int nbRow = row + directions[i][0];
                    int nbCol = col + directions[i][1];

                    if (nbRow >= 0 && nbRow < ROWS && nbCol >= 0 && nbCol < COLS) {
                        if (grid[nbRow][nbCol] == 1) {
                            grid[nbRow][nbCol] = 2;
                            --freshOrgs;

                            q.push(std::make_pair(nbRow, nbCol));
                            ++levelLen;
                        }
                    }
                }
            }
            ++minsElapsed;
            len = levelLen;
        }

        return freshOrgs == 0 ? minsElapsed : -1;
    }
};