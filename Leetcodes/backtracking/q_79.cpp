/*
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Example 2:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true

Example 3:

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false

 

Constraints:

    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board and word consists of only lowercase and uppercase English letters.

*/

class Solution {
private:
    bool backtracking(vector<vector<char>>& board, string& word) {
        std::size_t rows = board.size();
        std::size_t cols = board[0].size();
        std::size_t w_len = word.size();
        std::array<std::array<int, 4>, 4> dir{{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} }};

        std::function<bool(int, int, int)> bt = [&](int i, int j, int cnt_now) -> bool {
            if (cnt_now == w_len) {
                return true;
            }

            if (i >= rows || j >= cols || i < 0 || j < 0 || board[i][j] != word[cnt_now]) {
                return false;
            }

            char tmp = board[i][j];
            board[i][j] = '#';
            for (const auto& d : dir) {

                int next_r = i + d[0];
                int next_c = j + d[1];

                if (bt(next_r, next_c, cnt_now + 1)) {
                    return true;
                }
            }
            board[i][j] = tmp;

            return false;
        };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (bt(r, c, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        return backtracking(board, word);
    }
};