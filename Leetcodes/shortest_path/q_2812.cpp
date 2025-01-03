/*
You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:

    A cell containing a thief if grid[r][c] = 1
    An empty cell if grid[r][c] = 0

You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.

The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.

Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).

An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.

The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.

 

Example 1:

Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
Output: 0
Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).

Example 2:

Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 2) is cell (0, 0). The distance between them is | 0 - 0 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.

Example 3:

Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
Output: 2
Explanation: The path depicted in the picture above has a safeness factor of 2 since:
- The closest cell of the path to the thief at cell (0, 3) is cell (1, 2). The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
- The closest cell of the path to the thief at cell (3, 0) is cell (3, 2). The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
It can be shown that there are no other paths with a higher safeness factor.

 

Constraints:

    1 <= grid.length == n <= 400
    grid[i].length == n
    grid[i][j] is either 0 or 1.
    There is at least one thief in the grid.


*/

class Solution {
private:
    int N = 0;
    int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} }; //row, col 

    bool is_valid_cell(int row, int col) {
        if (row < 0 || row >= N || col < 0 || col >= N) {
            return false;
        }

        return true;
    };

    void set_safeness_for_all_cells(vector<vector<int>>& grid) {
        std::queue<std::pair<int, int>> q;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (grid[r][c] == 1) {
                    q.push({r, c});
                    grid[r][c] = 0;     //distance to the thief
                } else {
                    grid[r][c] = -1;    //marked as unvisited
                }
            }
        }

        while (!q.empty()) {

            int len = q.size();
            for (int i = 0; i < len; ++i) {
                auto curr = q.front();
                q.pop();

                for (const auto& d : dirs) {
                    int r = curr.first + d[0];
                    int c = curr.second + d[1];
                    int val = grid[curr.first][curr.second];

                    if (is_valid_cell(r, c) && grid[r][c] == -1) {
                        grid[r][c] = val + 1;
                        q.push({r, c});
                    }
                }
            }
        }
    }
    bool is_valid_safeness(vector<vector<int>>& grid, int min_safeness) {

        if (grid[0][0] < min_safeness || grid[N - 1][N - 1] < min_safeness) {
            return false;
        }

        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));

        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();

            if (curr.first == N - 1 && curr.second == N - 1) {
                return true;
            }

            for (const auto& d : dirs) {
                int r = curr.first + d[0];
                int c = curr.second + d[1];

                if (is_valid_cell(r, c) && !visited[r][c] && grid[r][c] >= min_safeness) {
                    visited[r][c] = true;
                    q.push({r, c});
                }
            }
        }

        return false;
    }

    int bfs_and_binarysearch(vector<vector<int>>& grid) {

        set_safeness_for_all_cells(grid);

        int start = 0;
        int end = 0;
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                end = std::max(end, grid[r][c]);
            }
        }

        //do binary search
        int ans = -1;
        while (start <= end) {
            int mid = start + (end - start) / 2;

            if (is_valid_safeness(grid, mid)) {
                ans = mid;
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }

        return ans;
    }

    int byDijstra(vector<vector<int>>& grid) {

        set_safeness_for_all_cells(grid);

        std::priority_queue<std::tuple<int, int, int>> pq;  //safeness, row, col
        pq.push({grid[0][0], 0, 0});
        grid[0][0] = -1; //marked as visited

        while (!pq.empty()) {
            const auto [s, r, c] = pq.top();
            pq.pop();

            if (r == N - 1 && c == N - 1) {
                return s;
            }

            for (const auto& d : dirs) {
                int next_r = d[0] + r;
                int next_c = d[1] + c;

                if (is_valid_cell(next_r, next_c) && grid[next_r][next_c] != -1) {
                    //why minimum?
                    //by definition, The safeness factor of a path on the grid: 
                    //the minimum manhattan distance from any cell in the path to any thief in the grid.
                    //And because it is max pq, it means we will get max among those min vals;
                    pq.push({std::min(s, grid[next_r][next_c]), next_r, next_c});
                    grid[next_r][next_c] = -1;
                }
            }
        }

        return -1;
    }
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        N = grid.size();

        //corner case
        if (grid[0][0] == 1 || grid[N - 1][N - 1] == 1) {
            return 0;
        }

        //corner case, neighbors of begin or end are all thieves
        if ((grid[1][0] == 1 && grid[0][1] == 1) || 
            (grid[N - 1][N - 2] == 1 && grid[N - 2][N - 1] == 1)) {
            return 0;
        }

        //corner case, on diagnal, all thieves
        bool all_thieves = true;
        for (int r = 0; r < N; ++r) {
            if (grid[r][N - r - 1] != 1) {
                all_thieves = false;
                break;
            }
        }

        if (all_thieves) {
            return 0;
        }

        //return bfs_and_binarysearch(grid);
        return byDijstra(grid);
    }
};