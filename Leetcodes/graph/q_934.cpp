/*
You are given an n x n binary matrix grid where 1 represents land and 0 represents water.

An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.

You may change 0's to 1's to connect the two islands to form one island.

Return the smallest number of 0's you must flip to connect the two islands.

 

Example 1:

Input: grid = [[0,1],[1,0]]
Output: 1

Example 2:

Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
Output: 2

Example 3:

Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
Output: 1

 

Constraints:

    n == grid.length == grid[i].length
    2 <= n <= 100
    grid[i][j] is either 0 or 1.
    There are exactly two islands in grid.


*/

class Solution {
    void dfs(vector<vector<int>>& grid, int r, int c, int n, 
                    std::vector<std::pair<int, int>>& dirs, std::queue<std::pair<int, int>>& q) {

        grid[r][c] = 2;

        //only add nodes that were next to ocean
        for (auto& p : dirs) {
            int currR = p.first + r;
            int currC = p.second + c;

            if (currR >= 0 && currR < n && currC >= 0 && currC < n && grid[currR][currC] == 0) {
                q.push({r, c});
                break;
            }
        }

        for (auto& p : dirs) {
            int currR = p.first + r;
            int currC = p.second + c;

            if (currR >= 0 && currR < n && currC >= 0 && currC < n && grid[currR][currC] == 1) {
                dfs(grid, currR, currC, n, dirs, q);
            }
        }
    }

    int bfs(int n, vector<vector<int>>& grid, std::queue<std::pair<int, int>>& q, 
                                            std::vector<std::pair<int, int>>& dirs) {

        int distance = 0;
        while (!q.empty()) {
            std::queue<std::pair<int, int>> newQueue;
            
            while (!q.empty()) {
                auto location = q.front();  //can not use auto& here!!
                q.pop();

                int r = location.first;
                int c = location.second;
                for (auto& p : dirs) {

                    int currR = r + p.first;
                    int currC = c + p.second;

                    if (currR >= 0 && currR < n && currC >= 0 && currC < n) {

                        if (grid[currR][currC] == 1) {
                            return distance;

                        } else if (grid[currR][currC] == 0) {
                            newQueue.push({currR, currC});
                            grid[currR][currC] = -1;
                        }
                    }
                }
                
            }

            q = newQueue;
            ++distance;
        }

        return distance;
    }
public:
    int shortestBridge(vector<vector<int>>& grid) {

        //find first island point
        int n = grid.size();

        int firstR = -1;
        int firstC = -1;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    firstR = r;
                    firstC = c;
                    break;
                }
            }

            if (firstR != -1 && firstC != -1) {
                break;
            }
        }

        //set four direction
        std::vector<std::pair<int, int>> dirs{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        std::queue<std::pair<int, int>> q;
        //filled first island to 2
        dfs(grid, firstR, firstC, n, dirs, q);

        //using bfs to find shortest path
        return bfs(n, grid, q, dirs);
    }
};