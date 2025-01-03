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
    void bfs(vector<vector<int>>& heights, std::queue<std::pair<int, int>>& q, std::vector<std::vector<bool>>& reachable, 
                                    int rows, int cols, std::vector<std::pair<int, int>>& directions) {

        while (!q.empty()) {
            std::pair<int, int> node = q.front();
            q.pop();
            int currR = node.first;
            int currC = node.second;

            reachable[currR][currC] = true;

            for (const std::pair<int, int>& p : directions) {
                int newR = currR + p.first;
                int newC = currC + p.second;

                //!!! most important if else logic !!!
                if (newR >= 0 && newR < rows && newC >= 0 && newC < cols && 
                        !reachable[newR][newC] && heights[newR][newC] >= heights[currR][currC]) {

                    q.push({newR, newC});
                }
            }
        }
    }
    vector<vector<int>> by_bfs(vector<vector<int>>& heights) {
        
        int rows = heights.size();
        int cols = heights[0].size();

        //corner case, only one cell
        if (rows == 1 && cols == 1) {
            return {{0, 0}};
        }
        //corner case, only one row
        if (rows == 1 && cols > 1) {
            std::vector<std::vector<int>> result;

            for (int c = 0; c < heights[0].size(); ++c) {
                result.push_back({0, c});
            }

            return result;
        }
        //corner case, only one column
        if (rows > 1 && cols == 1) {
            std::vector<std::vector<int>> result;

            for (int r = 0; r < heights.size(); ++r) {
                result.push_back({r, 0});
            }

            return result;
        }
        
        std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::queue<std::pair<int, int>> pacific_q;
        std::queue<std::pair<int, int>> atlantic_q;

        //for row top close to pacific and bottom close to atlantic
        for (int c = 0; c < cols; ++c) {
            pacific_q.push({0, c});
            atlantic_q.push({rows - 1, c});
        }

        //for col left close to pacific and right close to atlantic
        for (int r = 0; r < rows; ++r) {
            pacific_q.push({r, 0});
            atlantic_q.push({r, cols - 1});
        }

        std::vector<std::vector<bool>> pacificReachable(rows, std::vector<bool>(cols));
        std::vector<std::vector<bool>> atlanticReachable(rows, std::vector<bool>(cols));

        bfs(heights, pacific_q, pacificReachable, rows, cols, directions);
        bfs(heights, atlantic_q, atlanticReachable, rows, cols, directions);
        
        std::vector<std::vector<int>> result;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (pacificReachable[r][c] && atlanticReachable[r][c]) {
                    result.push_back({r, c});
                }
            }
        }
        
        return result;
    }

public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        return by_bfs(heights);
    }
};