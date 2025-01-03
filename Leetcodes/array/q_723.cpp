/*
This question is about implementing a basic elimination algorithm for Candy Crush.

Given an m x n integer array board representing the grid of candy where board[i][j] represents the type of candy. A value of board[i][j] == 0 represents that the cell is empty.

The given board represents the state of the game following the player's move. Now, you need to restore the board to a stable state by crushing candies according to the following rules:

    If three or more candies of the same type are adjacent vertically or horizontally, crush them all at the same time - these positions become empty.
    After crushing all candies simultaneously, if an empty space on the board has candies on top of itself, then these candies will drop until they hit a candy or bottom at the same time. No new candies will drop outside the top boundary.
    After the above steps, there may exist more candies that can be crushed. If so, you need to repeat the above steps.
    If there does not exist more candies that can be crushed (i.e., the board is stable), then return the current board.

You need to perform the above rules until the board becomes stable, then return the stable board.

 

Example 1:

Input: board = [[110,5,112,113,114],[210,211,5,213,214],[310,311,3,313,314],[410,411,412,5,414],[5,1,512,3,3],[610,4,1,613,614],[710,1,2,713,714],[810,1,2,1,1],[1,1,2,2,2],[4,1,4,4,1014]]
Output: [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[110,0,0,0,114],[210,0,0,0,214],[310,0,0,113,314],[410,0,0,213,414],[610,211,112,313,614],[710,311,412,613,714],[810,411,512,713,1014]]

Example 2:

Input: board = [[1,3,5,5,2],[3,4,3,3,1],[3,2,4,5,2],[2,4,4,5,5],[1,4,4,1,1]]
Output: [[1,3,0,0,0],[3,4,0,5,2],[3,2,0,3,1],[2,4,0,5,2],[1,4,3,1,1]]

 

Constraints:

    m == board.length
    n == board[i].length
    3 <= m, n <= 50
    1 <= board[i][j] <= 2000


*/


struct m_hash {
    template<class T1, class T2>
    size_t operator() (const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

class Solution {
private:
    void find(vector<vector<int>>& board, int rows, int cols, 
                    std::unordered_set<std::pair<int, int>, m_hash>& needCrush) {

        //left and right side for vertical check
        for (int r = 1; r < rows - 1; ++r) {

            //left
            if (board[r][0] != 0 && board[r][0] == board[r - 1][0] && 
                                            board[r][0] == board[r + 1][0]) {

                needCrush.insert({r, 0});
                needCrush.insert({r - 1, 0});
                needCrush.insert({r + 1, 0});
            }

            //right
            if (board[r][cols - 1] != 0 && board[r][cols - 1] == board[r - 1][cols - 1] && 
                                                board[r][cols - 1] == board[r + 1][cols - 1]) {

                needCrush.insert({r, cols - 1});
                needCrush.insert({r - 1, cols - 1});
                needCrush.insert({r + 1, cols - 1});
            }
        }

        //top and bottom side for horizontal check
        for (int c = 1; c < cols - 1; ++c) {
            //top
            if (board[0][c] != 0 && board[0][c] == board[0][c - 1] && 
                                            board[0][c] == board[0][c + 1]) {

                needCrush.insert({0, c});
                needCrush.insert({0, c - 1});
                needCrush.insert({0, c + 1});
            }

            //bottom
            if (board[rows - 1][c] != 0 && board[rows - 1][c] == board[rows - 1][c - 1] && 
                                            board[rows - 1][c] == board[rows - 1][c + 1]) {

                needCrush.insert({rows - 1, c});
                needCrush.insert({rows - 1, c - 1});
                needCrush.insert({rows - 1, c + 1});
            }
        }

        //inner elements do vertical check and horizontal check
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                
                if (board[r][c] != 0) {
                    //horizontal
                    if (board[r][c] == board[r][c - 1] && board[r][c] == board[r][c + 1]) {
                        needCrush.insert({r, c});
                        needCrush.insert({r, c - 1});
                        needCrush.insert({r, c + 1});
                    }
                    //vertical
                    if (board[r][c] == board[r - 1][c] && board[r][c] == board[r + 1][c]) {
                        needCrush.insert({r, c});
                        needCrush.insert({r - 1, c});
                        needCrush.insert({r + 1, c});
                    }
                }
            }
        }

        int i = 0;
    }

    void crush(vector<vector<int>>& board, int rows, int cols, 
                    std::unordered_set<std::pair<int, int>, m_hash>& needCrush) {
        
        for (const auto& p : needCrush) {
            board[p.first][p.second] = 0;
        }

        int i = 0;
    }

    void drop(vector<vector<int>>& board, int rows, int cols) {

        //do drop by column
        for (int c = 0; c < cols; ++c) {
            int lowestZero = -1;

            //iterate from bottom
            for (int r = rows - 1; r > -1; --r) {
                if (board[r][c] == 0) {

                    lowestZero = std::max(lowestZero, r);

                } else if (lowestZero >= 0) {

                    int val = board[r][c];
                    board[r][c] = 0;
                    board[lowestZero][c] = val;

                    --lowestZero;
                }
            }
        }
    }

public:
    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int rows = board.size();
        int cols = board[0].size();
        std::unordered_set<std::pair<int, int>, m_hash> needCrush;

        find(board, rows, cols, needCrush);

        //elements for crushing, we will set them zero!!!
        while (!needCrush.empty()) {
            crush(board, rows, cols, needCrush);
            drop(board, rows, cols);

            //clear this set for next check
            needCrush.clear();
            find(board, rows, cols, needCrush);
        }

        return board;
    }
};