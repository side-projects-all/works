/*

*/

class Solution {
private:
    bool is_valid(std::vector<std::vector<bool>>& visited, int r, int c) {
        return r >= 0 && r < visited.size() && c >= 0 && c < visited[0].size() && !visited[r][c];
    }
public:
    int minimumTime(vector<vector<int>>& grid) {
        if (grid[0][1] > 1 && grid[1][0] > 1) {
            return -1;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        int dirs[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        std::priority_queue<std::tuple<int, int, int>, 
                            std::vector<std::tuple<int, int, int>>, 
                            std::greater<std::tuple<int, int, int>>> pq;
        pq.push({grid[0][0], 0, 0});

        while (!pq.empty()) {
            auto [time, row, col] = pq.top();
            pq.pop();

            if (row == rows - 1 && col == cols - 1) {
                return time;
            }

            if (visited[row][col]) {
                continue;
            }

            visited[row][col] = true;

            for (auto& d : dirs) {
                int next_r = row + d[0];
                int next_c = col + d[1];

                if (!is_valid(visited, next_r, next_c)) {
                    continue;
                }

                int wait_time = ((grid[next_r][next_c] - time) % 2 == 0) ? 1 : 0;
                int next_time = std::max(grid[next_r][next_c] + wait_time, time + 1);

                pq.push({next_time, next_r, next_c});
            }
        }

        return -1;
    }
};