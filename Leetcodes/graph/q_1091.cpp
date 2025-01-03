/*
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.

A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:

    All the visited cells of the path are 0.
    All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).

The length of a clear path is the number of visited cells of this path.

 

Example 1:

Input: grid = [[0,1],[1,0]]
Output: 2

Example 2:

Input: grid = [[0,0,0],[1,1,0],[1,1,0]]
Output: 4

Example 3:

Input: grid = [[1,0,0],[1,1,0],[1,1,0]]
Output: -1

 

Constraints:

    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1


*/

class Solution {
private:
    int bfs(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        //corner cases
        if (grid[0][0] == 1 || grid[rows - 1][cols - 1] == 1) {
            return -1;
        }

        if (rows == 1 && cols == 1 && grid[rows - 1][cols - 1] == 0) {
            return 1;
        }

        //we could try not to use additional array to store temp result
        //std::vector<std::vector<int>> result(grid);
        std::pair<int, int> directions[8] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
                                                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        //std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        std::queue<std::vector<int>> q;

        q.push({0, 0, 1});
        
        while (!q.empty()) {
            std::vector<int> pos = q.front();
            q.pop();

            int r = pos[0];
            int c = pos[1];
            int steps = pos[2];

            if (r == rows - 1 && c == cols - 1) {
                return steps;
            }

            /*
            if (visited[r][c]) {
                continue;
            }

            visited[r][c] = true;
            */
            
            for (auto& p : directions) {
                int nextR = r + p.first;
                int nextC = c + p.second;

                /*
                if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols 
                                                    && grid[nextR][nextC] == 0 && !visited[nextR][nextC]) {
                */
                if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols 
                                                    && grid[nextR][nextC] == 0) {
                    //result[nextR][nextC] = steps + 1;
                    q.push({nextR, nextC, steps + 1});

                    //change the value of valid neighbor, then we will not visited them again
                    grid[nextR][nextC] = steps + 1;
                }
            }
        }

        return -1;
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        return bfs(grid);
    }
};