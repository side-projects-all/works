/*
You are given an m x n grid rooms initialized with these three possible values.

    -1 A wall or an obstacle.
    0 A gate.
    INF Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.

Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

 

Example 1:

Input: rooms = [[2147483647,-1,0,2147483647],[2147483647,2147483647,2147483647,-1],[2147483647,-1,2147483647,-1],[0,-1,2147483647,2147483647]]
Output: [[3,-1,0,1],[2,2,1,-1],[1,-1,2,-1],[0,-1,3,4]]

Example 2:

Input: rooms = [[-1]]
Output: [[-1]]

 

Constraints:

    m == rooms.length
    n == rooms[i].length
    1 <= m, n <= 250
    rooms[i][j] is -1, 0, or 2^31 - 1.


*/

class Solution {
private:
    void byBFS(vector<vector<int>>& rooms) {
        int rows = rooms.size();
        int cols = rooms[0].size();

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        std::queue<std::pair<int, int>> q;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (rooms[r][c] == 0) {
                    q.push({r, c});
                }
            }
        }

        while (!q.empty()) {
            auto [r_now, c_now] = q.front();
            q.pop();

            for (auto& dir : dirs) {
                int r_next = r_now + dir[0];
                int c_next = c_now + dir[1];

                if (r_next >= 0 && r_next < rows && c_next >= 0 && c_next < cols && 
                                                            rooms[r_next][c_next] == INT_MAX) {

                    rooms[r_next][c_next] = rooms[r_now][c_now] + 1;
                    q.push({r_next, c_next});
                }
            }
        }
    }
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        byBFS(rooms);
    }
};