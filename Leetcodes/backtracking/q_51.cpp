/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle. You may return the answer in any order.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.

 

Example 1:

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above

Example 2:

Input: n = 1
Output: [["Q"]]

 

Constraints:

    1 <= n <= 9


*/

class Solution {
private:
    void backtracking(int col, int& n, std::vector<std::string>& board, 
        std::vector<std::vector<std::string>>& ans, std::vector<bool>& left_rows, 
                        std::vector<bool>& diag, std::vector<bool>& rev_diag) {
        if (col == n) {
            ans.push_back(board);
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
    vector<vector<string>> by_backtracking(int& n) {
        std::vector<std::vector<std::string>> ans;
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<bool> left_rows(n);
        std::vector<bool> diag(2 * n - 1);
        std::vector<bool> rev_diag(2 * n - 1);
        backtracking(0, n, board, ans, left_rows, diag, rev_diag);

        return ans;
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        return by_backtracking(n);
    }
};