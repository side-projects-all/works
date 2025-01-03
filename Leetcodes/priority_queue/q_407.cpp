/*

*/

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int vol = 0;
        const int rows = heightMap.size();
        const int cols = heightMap[0].size();

        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
        int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

        auto cmpr = [](const std::array<int, 3>& a, const std::array<int, 3>& b) -> bool {
            return a[0] > b[0];
        };

        std::priority_queue<std::array<int, 3>, std::vector<std::array<int, 3>>, decltype(cmpr)> pq;

        //top and bottom boundary
        for (int i = 0; i < cols; ++i) {
            pq.push({ heightMap[0][i], 0, i });
            pq.push({ heightMap[rows - 1][i], rows - 1, i });
            visited[0][i] = true;
            visited[rows - 1][i] = true;
        }
        //left and right boundary
        for (int i = 0; i < rows; ++i) {
            pq.push({ heightMap[i][0], i, 0 });
            pq.push({ heightMap[i][cols - 1], i, cols - 1 });
            visited[i][0] = true;
            visited[i][cols - 1] = true;
        }

        while (!pq.empty()) {
            auto [h, r, c] = pq.top();
            pq.pop();

            for (auto d : dir) {
                int next_r = r + d[0];
                int next_c = c + d[1];

                if (next_r >= 0 && next_r < rows && 
                        next_c >= 0 && next_c < cols && 
                                !visited[next_r][next_c]) {
                    
                    visited[next_r][next_c] = true;

                    if (heightMap[next_r][next_c] < h) {
                        vol += h - heightMap[next_r][next_c];
                    }

                    pq.push({ std::max(h, heightMap[next_r][next_c]), next_r, next_c });
                }
            }
        }

        return vol;
    }
};