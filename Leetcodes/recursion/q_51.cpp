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
public:
    vector<vector<string>> solveNQueens(int n) {
        len = n;
        std::vector<std::vector<char>> state = std::vector<std::vector<char>>(len, 
                                                            std::vector<char>(len, '.'));
        
        std::unordered_set<int> diagonal;
        std::unordered_set<int> antiDiagonal;
        std::unordered_set<int> cols;

        backtrack(0, diagonal, antiDiagonal, cols, state);

        return result;
    }

private:
    int len;
    std::vector<std::vector<std::string>> result;
    //std::unordered_set<int> diagonal;
    //std::unordered_set<int> antiDiagonal;
    //std::unordered_set<int> cols;
    //std::vector<std::vector<char>> state;

    std::vector<string> createBoard(std::vector<std::vector<char>> &state) {
    //std::vector<string> createBoard() {
        std::vector<string> board(len);
        
        for (int row = 0; row < len; ++row) {
            std::string curr(state[row].begin(), state[row].end());
            board[row] = curr;
        }

        return board;
    }

    void backtrack(int row, std::unordered_set<int> &diagonal, 
                    std::unordered_set<int> &antiDiagonal, std::unordered_set<int> &cols, 
                    std::vector<std::vector<char>> &state) {
    //void backtrack(int row) {
        if (row == len) {
            result.push_back(createBoard(state));
            return;
        }

        for (int col = 0; col < len; ++col) {
            int currDiagonal = row - col;
            int currAntiDiagonal = row + col;

            if (cols.find(col) != cols.end() || 
                diagonal.find(currDiagonal) != diagonal.end() || 
                antiDiagonal.find(currAntiDiagonal) != antiDiagonal.end()) {

                continue;
            }

            cols.insert(col);
            diagonal.insert(currDiagonal);
            antiDiagonal.insert(currAntiDiagonal);
            state[row][col] = 'Q';

            backtrack(row + 1, diagonal, antiDiagonal, cols, state);
            cols.erase(col);
            diagonal.erase(currDiagonal);
            antiDiagonal.erase(currAntiDiagonal);
            state[row][col] = '.';
        }
    }
};