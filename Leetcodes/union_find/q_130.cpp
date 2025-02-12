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
private:
    class Union_find {
    private:
        std::vector<int> parent;
    public:
        Union_find(int n) {
            parent.resize(n);
            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
        }

        int find(int x) {
            if (parent[x] == x) {
                return x;
            }

            return parent[x] = find(parent[x]);
        }

        void union_set(int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return;
            }

            parent[px] = py;
        }

        bool is_conn(int x, int y) {
            return find(x) == find(y);
        }
    };
    void by_union_find(vector<vector<char>>& board, int& rows, int& cols) {
        //dummy is rows * cols
        int dummy = rows * cols;
        Union_find uf(dummy + 1);

        //connect (r, c) with dummy if it were one boarder
        //else, connect with neighbor that is 'O'
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {

                if (board[r][c] != 'O') {
                    continue;
                }
                
                if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1) {
                    uf.union_set(r * cols + c, dummy);

                } else {

                    //union with neighbors
                    if (r > 0 && board[r - 1][c] == 'O') {
                        uf.union_set(r * cols + c, (r - 1) * cols + c);
                    }

                    if (r < rows - 1 && board[r + 1][c] == 'O') {
                        uf.union_set(r * cols + c, (r + 1) * cols + c);
                    }

                    if (c > 0 && board[r][c - 1] == 'O') {
                        uf.union_set(r * cols + c, r * cols + (c - 1));
                    }

                    if (c < cols - 1 && board[r][c + 1] == 'O') {
                        uf.union_set(r * cols + c, r * cols + (c + 1));
                    }
                }
            }
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'O' && uf.is_conn(r * cols + c, dummy) == false) {
                    board[r][c] = 'X';
                }
            }
        }
    }
    void dfs(vector<vector<char>>& board, int& rows, int& cols, int (&dirs)[4][2], int r, int c, char sign) {
        if (r < 0 || r == rows || c < 0 || c == cols || board[r][c] == 'X' || board[r][c] == 'E') {
            return;
        }

        board[r][c] = 'E';
        for (auto& d : dirs) {
            int next_r = r + d[0];
            int next_c = c + d[1];

            dfs(board, rows, cols, dirs, next_r, next_c, 'E');
        }
    }
    void by_dfs(vector<vector<char>>& board, int& rows, int& cols) {
        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') {
                dfs(board, rows, cols, dirs, r, 0, 'E');
            }

            if (board[r][cols - 1] == 'O') {
                dfs(board, rows, cols, dirs, r, cols - 1, 'E');
            }
        }

        for (int c = 0; c < cols; ++c) {
            if (board[0][c] == 'O') {
                dfs(board, rows, cols, dirs, 0, c, 'E');
            }

            if (board[rows - 1][c] == 'O') {
                dfs(board, rows, cols, dirs, rows - 1, c, 'E');
            }
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
    void by_bfs(vector<vector<char>>& board, int& rows, int& cols) {
        
        std::queue<std::pair<int, int>> q;
        for (int r = 0; r < rows; ++r) {
            if (board[r][0] == 'O') {
                q.push({r, 0});
            }

            if (board[r][cols - 1] == 'O') {
                q.push({r, cols - 1});
            }
        }

        for (int c = 0; c < cols; ++c) {
            if (board[0][c] == 'O') {
                q.push({0, c});
            }

            if (board[rows - 1][c] == 'O') {
                q.push({rows - 1, c});
            }
        }

        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (board[r][c] == 'E') {
                continue;
            }

            board[r][c] = 'E';

            for (auto& d : dirs) {
                int next_r = r + d[0];
                int next_c = c + d[1];

                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && board[next_r][next_c] == 'O') {
                    q.push({next_r, next_c});
                }
            }
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
public:
    void solve(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        if (rows == 1 || cols == 1) {
            return;
        }
        //by_bfs(board, rows, cols);
        //by_dfs(board, rows, cols);
        by_union_find(board, rows, cols);
    }
};