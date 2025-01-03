/*
You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.

A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

 

Example 1:

Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
Output: 7
Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
There are a total of 7 unguarded cells, so we return 7.

Example 2:

Input: m = 3, n = 3, guards = [[1,1]], walls = [[0,1],[1,0],[2,1],[1,2]]
Output: 4
Explanation: The unguarded cells are shown in green in the above diagram.
There are a total of 4 unguarded cells, so we return 4.

 

Constraints:

    1 <= m, n <= 10^5
    2 <= m * n <= 10^5
    1 <= guards.length, walls.length <= 5 * 10^4
    2 <= guards.length + walls.length <= m * n
    guards[i].length == walls[j].length == 2
    0 <= rowi, rowj < m
    0 <= coli, colj < n
    All the positions in guards and walls are unique.


*/

class Solution {
private:
    //gr: row of guard position, gc: column of gurad position
    //dr: direction of row to go, dc: direction of column to go
    void mark_guarded(std::vector<std::vector<int>>& grid, int gr, int gc, int& total) {

        //go up
        for (int r = gr - 1; r >= 0; --r) {
            if (grid[r][gc] == 2 || grid[r][gc] == 1) {
                break;
            }

            if (grid[r][gc] == 3) {
                continue;
            }

            grid[r][gc] = 3;
            --total;
        }

        //go down
        for (int r = gr + 1; r < grid.size(); ++r) {
            if (grid[r][gc] == 2 || grid[r][gc] == 1) {
                break;
            }

            if (grid[r][gc] == 3) {
                continue;
            }

            grid[r][gc] = 3;
            --total;
        }

        //go left
        for (int c = gc - 1; c >= 0; --c) {
            if (grid[gr][c] == 2 || grid[gr][c] == 1) {
                break;
            }

            if (grid[gr][c] == 3) {
                continue;
            }

            grid[gr][c] = 3;
            --total;
        }

        //go right
        for (int c = gc + 1; c < grid[0].size(); ++c) {
            if (grid[gr][c] == 2 || grid[gr][c] == 1) {
                break;
            }

            if (grid[gr][c] == 3) {
                continue;
            }

            grid[gr][c] = 3;
            --total;
        }
    }
public:
    int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
        std::vector<std::vector<int>> grid(m, std::vector<int>(n));
        int total = m * n;
        //mark position of guard as 1
        for (std::vector<int>& g : guards) {
            grid[g[0]][g[1]] = 1;
            --total;
        }
        //mark position of wall as 2
        for (std::vector<int>& w : walls) {
            grid[w[0]][w[1]] = 2;
            --total;
        }

        //start from every position of guard to go 4 directions
        for (std::vector<int>& g : guards) {

            for (int i = 0; i < 4; ++i) {
                mark_guarded(grid, g[0], g[1], total);
            }
        }
        
        return total;
    }
};