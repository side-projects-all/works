/*

*/

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        //using 0 and 1 to mark that cell if alreay putting a number or not
        //every row 0 to 8 has its value 1 to 9
        rows = std::vector<std::vector<int>>(len, std::vector<int>(len + 1, 0));
        //every col 0 to 8 has its value 1 to 9
        cols = std::vector<std::vector<int>>(len, std::vector<int>(len + 1, 0));
        //every box 0 to 8 has its value 1 to 9
        boxes = std::vector<std::vector<int>>(len, std::vector<int>(len + 1, 0));

        for (int i = 0; i < len; ++i) {
            for (int j = 0; j < len; ++j) {
                char num = board[i][j];

                if (num != '.') {
                    int d = (int)num - 48;
                    placeNum(d, i, j, board);
                }
            }
        }

        bactrack(0, 0, board);
        int i  = 0;
    }

private:
    //sub-box size
    int n = 3;
    int len = 9;
    std::vector<std::vector<int>> rows;
    std::vector<std::vector<int>> cols;
    std::vector<std::vector<int>> boxes;

    bool solved = false;

    void bactrack(int row, int col, std::vector<std::vector<char>> &board) {
        
        if (board[row][col] == '.') {
            for (int d = 1; d < 10; ++d) {
                if (placeable(d, row, col)) {
                    placeNum(d, row, col, board);

                    //decide to go to next column or row
                    placeNextNum(row, col, board);

                    if (!solved) {
                        removeNum(d, row, col, board);
                    }
                }
            }
        } else {
            placeNextNum(row, col, board);
        }
    }

    bool placeable(int d, int row, int col) {
        int index = (row / n) * n + col / n;

        return (rows[row][d] + cols[col][d] + boxes[index][d]) == 0;
    }

    void placeNum(int d, int row, int col, std::vector<std::vector<char>> &board) {
        //place number in (row, col) cell
        //because we number each 3x3 sub-area from 0 to 8 by row, 
        //we divide row by n = 3 first, 
        //then we could retrieve the integer-part value between 0 to 2, 
        //and then we multiply them with n = 3, we would have 0, 3, 6, 
        //and then using col divided by n = 3 again, 
        //we could  the integer-part value between 0 to 2, 
        //and then plus them together we would have 0-8 sub-area combined by row and col
        int index = (row / n) * n + col / n;

        ++rows[row][d];
        ++cols[col][d];
        ++boxes[index][d];
        board[row][col] = (char)(d + '0');

    }

    void removeNum(int d, int row, int col, std::vector<std::vector<char>> &board) {
        
        int index = (row / n) * n + col / n;

        //reverse movement
        --rows[row][d];
        --cols[col][d];
        --boxes[index][d];
        board[row][col] = '.';
    }

    void placeNextNum(int row, int col, std::vector<std::vector<char>> &board) {
        if ((col == (len - 1)) && (row == (len - 1))) {
            solved = true;
        } else {
            if (col == (len - 1)) {
                bactrack(row + 1, 0, board);
            } else {
                bactrack(row, col + 1, board);
            }
        }
    }

};