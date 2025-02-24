/*

*/

class Solution {
private:
    int by_bfs(vector<vector<char>>& grid) {
        int dirs[4][2]{ {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        std::pair<int, int> init_pos;
        int rows = grid.size();
        int cols = grid[0].size();

        //std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '*') {
                    init_pos.first = r;
                    init_pos.second = c;
                    //visited[r][c] = true;
                    break;
                }
            }
        }

        std::queue<std::pair<int, int>> q;
        q.push(init_pos);

        int len = 1;
        while (!q.empty()) {
            int level_len = q.size();

            for (int i = 0; i < level_len; ++i) {
                auto [r, c] = q.front();
                q.pop();

                for (auto& d : dirs) {
                    int next_r = r + d[0];
                    int next_c = c + d[1];

                    if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && grid[next_r][next_c] != 'X' /*&& !visited[next_r][next_c]*/) {
                        //visited[next_r][next_c] = true;

                        if (grid[next_r][next_c] == '#') {
                            return len;

                        } else if (grid[next_r][next_c] == 'O') {
                            q.push({next_r, next_c});
                        }

                        grid[next_r][next_c] = 'X';
                    }
                }
            }

            ++len;
        }

        return -1;
    }
public:
    int getFood(vector<vector<char>>& grid) {
        return by_bfs(grid);
    }
};