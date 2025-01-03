/*
Given an m x n matrix board containing 'X' and 'O', capture all regions that are 4-directionally surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

 

Example 1:

Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
Explanation: Notice that an 'O' should not be flipped if:
- It is on the border, or
- It is adjacent to an 'O' that should not be flipped.
The bottom 'O' is on the border, so it is not flipped.
The other three 'O' form a surrounded region, so they are flipped.

Example 2:

Input: board = [["X"]]
Output: [["X"]]

 

Constraints:

    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is 'X' or 'O'.


*/

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        if (rows == 0 || cols == 0) {
            return;
        }

        std::vector<std::pair<int, int>> board_Os;  //row, col
        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') {
                board_Os.push_back({r, 0});
            }
            
            if (board[r][cols - 1] == 'O') {
                board_Os.push_back({r, cols - 1});
            }
        }

        for (int c = 1; c < cols - 1; ++c) {
            if (board[0][c] == 'O') {
                board_Os.push_back({0, c});
            }
            
            if (board[rows - 1][c] == 'O') {
                board_Os.push_back({rows - 1, c});
            }
        }

        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        std::function<void(int, int)> bfs = [&](int r, int c) {

            std::queue<std::pair<int, int>> q;
            q.push({r, c});

            while (!q.empty()) {
                const auto [row, col] = q.front();
                q.pop();

                if (board[row][col] == 'E') {
                    continue;
                }
                
                board[row][col] = 'E';

                for (const auto& d : dirs) {
                    int new_r = d[0] + row;
                    int new_c = d[1] + col;
                    if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols && 
                        board[new_r][new_c] == 'O') {

                        q.push({new_r, new_c});
                    }
                }
            }
        };

        for (const auto& [row, col] : board_Os) {
            bfs(row, col);
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'O') {
                    board[r][c] = 'X';
                }

                if (board[r][c] == 'E') {
                    board[r][c] = 'O';
                }
            }
        }
    }
};