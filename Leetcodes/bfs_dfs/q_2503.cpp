/*
You are given an m x n integer matrix grid and an array queries of size k.

Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:

    If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
    Otherwise, you do not get any points, and you end this process.

After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.

Return the resulting array answer.

 

Example 1:

Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
Output: [5,8,1]
Explanation: The diagrams above show which cells we visit to get points for each query.

Example 2:

Input: grid = [[5,2,1],[1,1,2]], queries = [3]
Output: [0]
Explanation: We can not get any points because the value of the top left cell is already greater than or equal to 3.

 

Constraints:

    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    k == queries.length
    1 <= k <= 10^4
    1 <= grid[i][j], queries[i] <= 10^6


*/

class Solution {
private:
    vector<int> by_sorting_bfs(vector<vector<int>>& grid, vector<int>& queries) {
        int rows = grid.size();
        int cols = grid[0].size();

        int n = queries.size();
        std::vector<std::pair<int, int>> sorted_q(n);
        for (int i = 0; i < n; ++i) {
            sorted_q[i] = {queries[i], i};
        }

        std::sort(sorted_q.begin(), sorted_q.end());
        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> pq;
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        int dirs[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::vector<int> ans(n);
        int points = 0;

        pq.push({grid[0][0], 0, 0});    //val, r, c
        visited[0][0] = true;

        for (int i = 0; i < n; ++i) {
            int query_val = sorted_q[i].first;
            int query_index = sorted_q[i].second;

            while (!pq.empty() && query_val > std::get<0>(pq.top())) {
                auto [val, r, c] = pq.top();
                pq.pop();
                ++points;

                for (auto& d : dirs) {
                    int new_r = r + d[0];
                    int new_c = c + d[1];

                    if (new_r < 0 || new_r == rows || new_c < 0 || new_c == cols || visited[new_r][new_c]) {
                        continue;
                    }

                    pq.push({grid[new_r][new_c], new_r, new_c});
                    visited[new_r][new_c] = true;
                }
            }

            ans[query_index] = points;
        }

        return ans;
    }
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
        return by_sorting_bfs(grid, queries);
    }
};