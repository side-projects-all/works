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
public:
    int totalNQueens(int n) {
        len = n;

        std::unordered_set<int> diagonal; 
        std::unordered_set<int> antiDiagonal; 
        std::unordered_set<int> cols;

        backtrack(0, diagonal, antiDiagonal, cols);

        return result;
    }

private:
    int len = 0;
    int result = 0;

    void backtrack(int row, std::unordered_set<int> &diagonal, 
                    std::unordered_set<int> &antiDiagonal, std::unordered_set<int> &cols) {

        if (row == len) {
            ++result;
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
            
            backtrack(row + 1, diagonal, antiDiagonal, cols);
            cols.erase(col);
            diagonal.erase(currDiagonal);
            antiDiagonal.erase(currAntiDiagonal);
        }

    }

};