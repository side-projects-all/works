/*
Given an m x n matrix board where each cell is a battleship 'X' or empty '.', return the number of the battleships on board.

Battleships can only be placed horizontally or vertically on board. In other words, they can only be made of the shape 1 x k (1 row, k columns) or k x 1 (k rows, 1 column), where k can be of any size. At least one horizontal or vertical cell separates between two battleships (i.e., there are no adjacent battleships).

 

Example 1:

Input: board = [["X",".",".","X"],[".",".",".","X"],[".",".",".","X"]]
Output: 2

Example 2:

Input: board = [["."]]
Output: 0

 

Constraints:

    m == board.length
    n == board[i].length
    1 <= m, n <= 200
    board[i][j] is either '.' or 'X'.

 

Follow up: Could you do it in one-pass, using only O(1) extra memory and without modifying the values board?

*/

class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        return naive(board);
        
        //return better(board);
    }

private:
    int better(vector<vector<char>>& board) {
        const int rows = board.size();
        const int cols = board[0].size();
        int cnt = 0;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (board[r][c] == 'X') {
                    if ((r == 0) || (board[r - 1][c]) == '.') {
                        if ((c == 0) || (board[r][c - 1]) == '.') {
                            ++cnt;
                        }
                    }
                }
            }
        }
        return cnt;
    }
    int naive(vector<vector<char>>& board) {
        int cnt = 0;
        int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };   //r, c; up, down, right, left
        int rows = board.size();
        int cols = board[0].size();
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {

                if (board[r][c] == 'X') {
                    int i = 0;
                    board[r][c] = 'B';
                    int next_r = 0;
                    int next_c = 0;

                    for (; i < 4; ++i) {
                        next_r = r + dir[i][0];
                        next_c = c + dir[i][1];

                        if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && board[next_r][next_c] == 'X') {
                            break;
                        }
                    }

                    while (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && board[next_r][next_c] == 'X') {
                        board[next_r][next_c] = 'B';
                        next_r += dir[i][0];
                        next_c += dir[i][1];
                    }

                    ++cnt;
                }
            }
        }

        return cnt;
    }
};