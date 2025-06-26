/*
There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.

The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).

The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.

Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.

 

Example 1:

Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
[0,4]: [0,4] -> Pacific Ocean 
       [0,4] -> Atlantic Ocean
[1,3]: [1,3] -> [0,3] -> Pacific Ocean 
       [1,3] -> [1,4] -> Atlantic Ocean
[1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
       [1,4] -> Atlantic Ocean
[2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
       [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
[3,0]: [3,0] -> Pacific Ocean 
       [3,0] -> [4,0] -> Atlantic Ocean
[3,1]: [3,1] -> [3,0] -> Pacific Ocean 
       [3,1] -> [4,1] -> Atlantic Ocean
[4,0]: [4,0] -> Pacific Ocean 
       [4,0] -> Atlantic Ocean
Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.

Example 2:

Input: heights = [[1]]
Output: [[0,0]]
Explanation: The water can flow from the only cell to the Pacific and Atlantic oceans.

 

Constraints:

    m == heights.length
    n == heights[r].length
    1 <= m, n <= 200
    0 <= heights[r][c] <= 10^5


*/

class Solution {
private:
    void dfs(vector<vector<int>>& heights, int& rows, int& cols, vector<vector<bool>>& visited, const int (*dir)[2], int row, int col) {
        if (visited[row][col] == true) {
            return;
        }

        visited[row][col] = true;
        for (int i = 0; i < 4; ++i) {
            int next_r = row + dir[i][0];
            int next_c = col + dir[i][1];

            if (next_r < 0 || next_r >= rows || next_c < 0 || next_c >= cols || heights[row][col] > heights[next_r][next_c]) {
                continue;
            }

            dfs(heights, rows, cols, visited, dir, next_r, next_c);
        }
    }
    vector<vector<int>> by_dfs(vector<vector<int>>& heights) {
        int rows = heights.size();
        int cols = heights[0].size();
        int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        std::vector<std::vector<bool>> pac(rows, std::vector<bool>(cols));
        //pacific left
        for (int r = 0; r < rows; ++r) {
            dfs(heights, rows, cols, pac, dir, r, 0);
        }

        //pacific top
        for (int c = 0; c < cols; ++c) {
            dfs(heights, rows, cols, pac, dir, 0, c);
        }

        std::vector<std::vector<bool>> atl(rows, std::vector<bool>(cols));
        //atlantic right
        for (int r = 0; r < rows; ++r) {
            dfs(heights, rows, cols, atl, dir, r, cols - 1);
        }

        //atlantic bottom
        for (int c = 0; c < cols; ++c) {
            dfs(heights, rows, cols, atl, dir, rows - 1, c);
        }

        std::vector<std::vector<int>> ans;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (pac[r][c] && atl[r][c]) {
                    ans.push_back({r, c});
                }
            }
        }

        return ans;
    }
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        return by_dfs(heights);
    }
};