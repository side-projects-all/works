/*
You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:

    A stone '#'
    A stationary obstacle '*'
    Empty '.'

The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

 

Example 1:

Input: boxGrid = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]

Example 2:

Input: boxGrid = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]

Example 3:

Input: boxGrid = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]

 

Constraints:

    m == boxGrid.length
    n == boxGrid[i].length
    1 <= m, n <= 500
    boxGrid[i][j] is either '#', '*', or '.'.


*/

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
        int rows = box.size();
        int cols = box[0].size();
        std::vector<vector<char>> ans(cols, std::vector<char>(rows));

        //transpose the input grid to ans
        for (int c = 0; c < cols; ++c) {
            for (int r = 0; r < rows; ++r) {
                ans[c][r] = box[r][c];
            }
        }

        //reverse each row in the ans to complete the 90° rotation
        for (int i = 0; i < cols; i++) {
            std::reverse(ans[i].begin(), ans[i].end());
        }

        //apply gravity to let stones fall to the lowest possible empty cell in each column
        for (int c = 0; c < rows; ++c) {

            int empty_cell = cols - 1;  //from lowest to set empty cell with stone
            for (int r = cols - 1; r >= 0; --r) {
                //let the stone fall to empty cell
                if (ans[r][c] == '#') {
                    ans[r][c] = '.';
                    ans[empty_cell][c] = '#';
                    --empty_cell;
                }
                
                //handle an obstacle, reset empty_cell to the row directly above it
                if (ans[r][c] == '*') {
                    empty_cell = r - 1;
                }
            }
        }
        return ans;
    }
};