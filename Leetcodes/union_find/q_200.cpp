/*
Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1

Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'
*/

class Solution {
private:
    class Union_find {
    private:
        std::vector<int> parent;
        std::vector<int> rank;
        int cnt = 0;
    public:
        Union_find(vector<vector<char>>& grid) {
            int rows = grid.size();
            int cols = grid[0].size();
            parent.resize(rows * cols);
            rank.resize(rows * cols, 1);

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (grid[r][c] == '1') {
                        ++cnt;
                    }
                    parent[r * cols + c] = r * cols + c;
                }
            }
        }

        int find(int x) {
            if (parent[x] == x) {
                return x;
            }

            return parent[x] = find(parent[x]);
        }

        void union_set(int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return;
            }

            if (rank[px] > rank[py]) {
                parent[py] = px;

            } else if (rank[px] < rank[py]) {
                parent[px] = py;

            } else {
                parent[px] = py;
                rank[py] += 1;
            }

            --cnt;
        }

        int counts() {
            return cnt;
        }
    };
    int by_union_find(vector<vector<char>>& grid, int& rows, int& cols) {
        Union_find uf(grid);

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    grid[r][c] = '0';

                    if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                        uf.union_set(r * cols + c, (r - 1) * cols + c);
                    }

                    if (r + 1 < rows && grid[r + 1][c] == '1') {
                        uf.union_set(r * cols + c, (r + 1) * cols + c);
                    }

                    if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                        uf.union_set(r * cols + c, r * cols + (c - 1));
                    }

                    if (c + 1 < cols && grid[r][c + 1] == '1') {
                        uf.union_set(r * cols + c, r * cols + (c + 1));
                    }
                }
            }
        }

        return uf.counts();
    }
    int by_bfs(vector<vector<char>>& grid, int& rows, int& cols) {
        int dirs[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        int islands = 0;

        std::queue<std::pair<int, int>> q;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    
                    grid[r][c] = '0';

                    q.push({r, c});
                    while (!q.empty()) {
                        auto [row, col] = q.front();
                        q.pop();

                        for (auto& d : dirs) {
                            int next_r = row + d[0];
                            int next_c = col + d[1];

                            if (next_r < 0 || next_r == rows || next_c < 0 || next_c == cols || grid[next_r][next_c] == '0') {
                                continue;
                            }

                            grid[next_r][next_c] = '0';
                            q.push({next_r, next_c});
                        }
                    }
                }
            }
        }

        return islands;
    }
    void dfs(vector<vector<char>>& grid, int (&dirs)[4][2], int& rows, int& cols, int r, int c) {
        if (r < 0 || r == rows || c < 0 || c == cols || grid[r][c] == '0') {
            return;
        }

        grid[r][c] = '0';
        for (auto& d : dirs) {
            int next_r = r + d[0];
            int next_c = c + d[1];
            dfs(grid, dirs, rows, cols, next_r, next_c);
        }
    }
    int by_dfs(vector<vector<char>>& grid, int& rows, int& cols) {
        
        int dirs[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        int islands = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;
                    dfs(grid, dirs, rows, cols, r, c);
                }
            }
        }

        return islands;
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        //return by_dfs(grid, rows, cols);
        //return by_bfs(grid, rows, cols);
        return by_union_find(grid, rows, cols);
    }
};