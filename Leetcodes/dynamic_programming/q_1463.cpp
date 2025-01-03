/*
You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.

You have two robots that can collect cherries for you:

    Robot #1 is located at the top-left corner (0, 0), and
    Robot #2 is located at the top-right corner (0, cols - 1).

Return the maximum number of cherries collection using both robots by following the rules below:

    From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
    When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
    When both robots stay in the same cell, only one takes the cherries.
    Both robots cannot move outside of the grid at any moment.
    Both robots should reach the bottom row in grid.

 

Example 1:

Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
Output: 24
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
Total of cherries: 12 + 12 = 24.

Example 2:

Input: grid = [[1,0,0,0,0,0,1],[2,0,0,0,0,3,0],[2,0,9,0,0,0,0],[0,3,0,5,4,0,0],[1,0,2,3,0,0,6]]
Output: 28
Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
Cherries taken by Robot #1, (1 + 9 + 5 + 2) = 17.
Cherries taken by Robot #2, (1 + 3 + 4 + 3) = 11.
Total of cherries: 17 + 11 = 28.

 

Constraints:

    rows == grid.length
    cols == grid[i].length
    2 <= rows, cols <= 70
    0 <= grid[i][j] <= 100


*/
class Solution {
private:
    int iterative(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<std::vector<int>>> mem(rows, 
                                                    std::vector<std::vector<int>>(cols, 
                                                            std::vector<int>(cols, 0)));

        //init last row
        for (int c1 = 0; c1 < cols; ++c1) {
            for (int c2 = 0; c2 < cols; ++c2) {
                
                int result = 0;
                result += grid[rows - 1][c1];
                if (c1 != c2) {
                    result += grid[rows - 1][c2];
                }

                mem[rows - 1][c1][c2] = result;
            }
        }
        
        for (int r = rows - 2; r > -1; --r) {
            for (int c1 = 0; c1 < cols; ++c1) {
                for (int c2 = 0; c2 < cols; ++c2) {

                    int result = 0;
                    result += grid[r][c1];
                    if (c1 != c2) {
                        result += grid[r][c2];
                    }

                    int max = 0;
                    //three directions
                    for (int preC1 = c1 - 1; preC1 <= c1 + 1; ++preC1) {
                        for (int preC2 = c2 - 1; preC2 <= c2 + 1; ++preC2) {

                            if (preC1 >= 0 && preC1 < cols && preC2 >= 0 && preC2 < cols) {
                                max = std::max(max, mem[r + 1][preC1][preC2]);
                            }
                        }
                    }

                    result += max;

                    mem[r][c1][c2] = result;
                }
            }
        }

        return mem[0][0][cols - 1];
    }
    int recursive(vector<vector<int>>& grid, std::vector<std::vector<std::vector<int>>>& mem, int r, int c1, int c2) {
        int rows = grid.size();
        int cols = grid[0].size();

        if (c1 < 0 || c1 >= cols || c2 < 0 || c2 >= cols) {
            return 0;
        }

        if (mem[r][c1][c2] != -1) {
            return mem[r][c1][c2];
        }

        int result = 0;
        result += grid[r][c1];
        if (c1 != c2) {
            result += grid[r][c2];
        }

        if (r != rows - 1) {
            int maxVal = 0;
            //both robots have three directions: left, stay the same, right
            for (int n_c1 = c1 - 1; n_c1 <= c1 + 1; ++n_c1) {
                for (int n_c2 = c2 - 1; n_c2 <= c2 + 1; ++n_c2) {
                    maxVal = std::max(maxVal, recursive(grid, mem, r + 1, n_c1, n_c2));
                }
            }

            result += maxVal;
        }

        mem[r][c1][c2] = result;

        return result;
    }
public:
    int cherryPickup(vector<vector<int>>& grid) {
        /*
        int rows = grid.size();
        int cols = grid[0].size();
        std::vector<std::vector<std::vector<int>>> mem(rows, std::vector<std::vector<int>>(cols, std::vector<int>(cols, -1)));
        return recursive(grid, mem, 0, 0, cols -1);
        */

        return iterative(grid);
    }
};