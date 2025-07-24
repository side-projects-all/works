/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.

 

Example 1:

Input: n = 4
Output: 2
Explanation: There are two distinct solutions to the 4-queens puzzle as shown.

Example 2:

Input: n = 1
Output: 1

 

Constraints:

    1 <= n <= 9


*/

class Solution {
private:
    void backtracking(int col, int& n, std::vector<std::string>& board, 
        int& ans, std::vector<bool>& left_rows, 
                        std::vector<bool>& diag, std::vector<bool>& rev_diag) {
        if (col == n) {
            ++ans;
            return;
        }

        for (int row = 0; row < n; ++row) {
            if (left_rows[row] || diag[row - col + n - 1] || rev_diag[row + col]) {
                continue;
            }

            left_rows[row] = true;
            diag[row - col + n - 1] = true;
            rev_diag[row + col] = true;
            board[row][col] = 'Q';

            backtracking(col + 1, n, board, ans, left_rows, diag, rev_diag);

            board[row][col] = '.';
            rev_diag[row + col] = false;
            diag[row - col + n - 1] = false;
            left_rows[row] = false;
        }
    }
    int by_backtracking(int& n) {
        int ans = 0;
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<bool> left_rows(n);
        std::vector<bool> diag(2 * n - 1);
        std::vector<bool> rev_diag(2 * n - 1);
        backtracking(0, n, board, ans, left_rows, diag, rev_diag);

        return ans;
    }
public:
    int totalNQueens(int n) {
        return by_backtracking(n);
    }
};