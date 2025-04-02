/*
The demons had captured the princess and imprisoned her in the bottom-right corner of a dungeon. The dungeon consists of m x n rooms laid out in a 2D grid. Our valiant knight was initially positioned in the top-left room and must fight his way through dungeon to rescue the princess.

The knight has an initial health point represented by a positive integer. If at any point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so the knight loses health upon entering these rooms; other rooms are either empty (represented as 0) or contain magic orbs that increase the knight's health (represented by positive integers).

To reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

Return the knight's minimum initial health so that he can rescue the princess.

Note that any room can contain threats or power-ups, even the first room the knight enters and the bottom-right room where the princess is imprisoned.

 

Example 1:

Input: dungeon = [[-2,-3,3],[-5,-10,1],[10,30,-5]]
Output: 7
Explanation: The initial health of the knight must be at least 7 if he follows the optimal path: RIGHT-> RIGHT -> DOWN -> DOWN.

Example 2:

Input: dungeon = [[0]]
Output: 1

 

Constraints:

    m == dungeon.length
    n == dungeon[i].length
    1 <= m, n <= 200
    -1000 <= dungeon[i][j] <= 1000


*/

class Solution {
private:
    int by_iterative_dp(vector<vector<int>>& dungeon) {
        int rows = dungeon.size();
        int cols = dungeon[0].size();
        std::vector<std::vector<int>> dp(rows, std::vector<int>(cols)); //min hp to enter every cell
        
        dp[rows - 1][cols - 1] = dungeon[rows - 1][cols - 1] >= 0 ? 1 : 1 - dungeon[rows - 1][cols - 1];
        //preprocessing last column
        for (int r = rows - 2; r >= 0; --r) {
            dp[r][cols - 1] = dungeon[r][cols - 1] >= 0 ? std::max(1, dp[r + 1][cols - 1] - dungeon[r][cols - 1]) : -dungeon[r][cols - 1] + dp[r + 1][cols - 1];
        }
        //preprocessing last row
        for (int c = cols - 2; c >= 0; --c) {
            dp[rows - 1][c] = dungeon[rows - 1][c] >= 0 ? std::max(1, dp[rows - 1][c + 1] - dungeon[rows - 1][c]) : -dungeon[rows - 1][c] + dp[rows - 1][c + 1];
        }

        for (int r = rows - 2; r >= 0; --r) {
            for (int c = cols - 2; c >= 0; --c) {

                int from_right = 0;
                int from_bottom = 0;
                if (dungeon[r][c] >= 0) {
                    from_right = std::max(1, dp[r][c + 1] - dungeon[r][c]);
                    from_bottom = std::max(1, dp[r + 1][c] - dungeon[r][c]);
                } else {
                    from_right = -dungeon[r][c] + dp[r][c + 1];
                    from_bottom = -dungeon[r][c] + dp[r + 1][c];
                }
                dp[r][c] = std::min(from_right, from_bottom);
            }
        }

        return dp[0][0];
    }
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        return by_iterative_dp(dungeon);
    }
};