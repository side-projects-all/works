/*
On an n x n chessboard, a knight starts at the cell (row, column) and attempts to make exactly k moves. The rows and columns are 0-indexed, so the top-left cell is (0, 0), and the bottom-right cell is (n - 1, n - 1).

A chess knight has eight possible moves it can make, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.

Each time the knight is to move, it chooses one of eight possible moves uniformly at random (even if the piece would go off the chessboard) and moves there.

The knight continues moving until it has made exactly k moves or has moved off the chessboard.

Return the probability that the knight remains on the board after it has stopped moving.

 

Example 1:

Input: n = 3, k = 2, row = 0, column = 0
Output: 0.06250
Explanation: There are two moves (to (1,2), (2,1)) that will keep the knight on the board.
From each of those positions, there are also two moves that will keep the knight on the board.
The total probability the knight stays on the board is 0.0625.

Example 2:

Input: n = 1, k = 0, row = 0, column = 0
Output: 1.00000

 

Constraints:

    1 <= n <= 25
    0 <= k <= 100
    0 <= row, column <= n - 1


*/

class Solution {
private:
    int dir[8][2] = { {2, -1}, {2, 1}, {-2, -1}, {-2, 1}, {1, -2}, {1, 2}, {-1, -2}, {-1, 2} };

    double recursive(int n, int k, int row, int column) {

        std::vector<std::vector<std::vector<double>>> mem(k + 1, 
                            std::vector<std::vector<double>>(n, std::vector<double>(n, -1)));

        std::function<double(int, int, int)> recurr = [&](int moves, int r_now, int c_now) -> double {
            //base: backward to move to original position
            if (moves == 0) {
                if (r_now == row && c_now == column) {
                    return 1.0;
                } else {
                    return 0.0;
                }
            }

            if (mem[moves][r_now][c_now] != -1) {
                return mem[moves][r_now][c_now];
            }

            mem[moves][r_now][c_now] = 0;
            for (auto& v : dir) {
                int pre_r = r_now - v[0];
                int pre_c = c_now - v[1];

                if (pre_r >= 0 && pre_r < n && pre_c >= 0 && pre_c < n) {
                    mem[moves][r_now][c_now] += recurr(moves - 1, pre_r, pre_c) * 0.125;
                }
            }

            return mem[moves][r_now][c_now];
        };

        double prob = 0.0;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                prob += recurr(k, r, c);
            }
        }
        return prob;
    }
public:
    double knightProbability(int n, int k, int row, int column) {
        return recursive(n, k, row, column);
    }
};