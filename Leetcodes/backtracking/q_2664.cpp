/*
Given two positive integers m and n which are the height and width of a 0-indexed 2D-array board, a pair of positive integers (r, c) which is the starting position of the knight on the board.

Your task is to find an order of movements for the knight, in a manner that every cell of the board gets visited exactly once (the starting cell is considered visited and you shouldn't visit it again).

Return the array board in which the cells' values show the order of visiting the cell starting from 0 (the initial place of the knight).

Note that a knight can move from cell (r1, c1) to cell (r2, c2) if 0 <= r2 <= m - 1 and 0 <= c2 <= n - 1 and min(abs(r1 - r2), abs(c1 - c2)) = 1 and max(abs(r1 - r2), abs(c1 - c2)) = 2.

 

Example 1:

Input: m = 1, n = 1, r = 0, c = 0
Output: [[0]]
Explanation: There is only 1 cell and the knight is initially on it so there is only a 0 inside the 1x1 grid.

Example 2:

Input: m = 3, n = 4, r = 0, c = 0
Output: [[0,3,6,9],[11,8,1,4],[2,5,10,7]]
Explanation: By the following order of movements we can visit the entire board.
(0,0)->(1,2)->(2,0)->(0,1)->(1,3)->(2,1)->(0,2)->(2,3)->(1,1)->(0,3)->(2,2)->(1,0)

 

Constraints:

    1 <= m, n <= 5
    0 <= r <= m - 1
    0 <= c <= n - 1
    The inputs will be generated such that there exists at least one possible order of movements with the given condition


*/

class Solution {
public:
    vector<vector<int>> tourOfKnight(int m, int n, int r, int c) {
        std::vector<std::vector<int>> visited(m,std::vector<int>(n));

        visited[r][c] = -1;
        backtracking(m, n, r, c, 1, visited);
        visited[r][c] = 0;

        return visited;
    }
private:
    int moves[8][2] = { {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2} };
    int rows = 0;
    int cols = 0;

    bool is_valid_move(std::vector<std::vector<int>>& visited, int r, int c) {
        return r >= 0 && r < visited.size() && c >= 0 && c < visited[0].size() && visited[r][c] == 0;
    }
    int cnt_valid_moves(std::vector<std::vector<int>>& visited, int r, int c) {
        int cnt = 0;
        for (int i = 0; i < 8; ++i) {
            int next_r = r + moves[i][0];
            int next_c = c + moves[i][1];

            if (is_valid_move(visited, next_r, next_c)) {
                ++cnt;
            }
        }

        return cnt;
    }
    std::vector<std::pair<int, int>> warnsdorff(std::vector<std::vector<int>>& visited, int r, int c) {
        std::vector<std::pair<int, int>> next_moves;
        for (int i = 0; i < 8; ++i) {
            int next_r = r + moves[i][0];
            int next_c = c + moves[i][1];

            int score = cnt_valid_moves(visited, next_r, next_c);

            next_moves.push_back({score, i});
        }
        std::sort(next_moves.begin(), next_moves.end());
        return next_moves;
    }
    bool backtracking(int& rows, int& cols, int r, int c, int cnt, std::vector<std::vector<int>>& visited) {
        if (cnt == rows * cols) {
            return true;
        }

        std::vector<std::pair<int, int>> next_moves = warnsdorff(visited, r, c);

        for (auto& m : next_moves) {
            int next_r = r + moves[m.second][0];
            int next_c = c + moves[m.second][1];

            if (!is_valid_move(visited, next_r, next_c)) {
                continue;
            }

            visited[next_r][next_c] = cnt;
            if (backtracking(rows, cols, next_r, next_c, cnt + 1, visited)) {
                return true;
            }

            visited[next_r][next_c] = 0;
        }

        return false;
    }
};