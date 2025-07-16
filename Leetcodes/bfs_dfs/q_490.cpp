/*
There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction.

Given the m x n maze, the ball's start position and the destination, where start = [startrow, startcol] and destination = [destinationrow, destinationcol], return true if the ball can stop at the destination, otherwise return false.

You may assume that the borders of the maze are all walls (see examples).

 

Example 1:

Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [4,4]
Output: true
Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.

Example 2:

Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], start = [0,4], destination = [3,2]
Output: false
Explanation: There is no way for the ball to stop at the destination. Notice that you can pass through the destination but you cannot stop there.

Example 3:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], start = [4,3], destination = [0,1]
Output: false

 

Constraints:

    m == maze.length
    n == maze[i].length
    1 <= m, n <= 100
    maze[i][j] is 0 or 1.
    start.length == 2
    destination.length == 2
    0 <= startrow, destinationrow <= m
    0 <= startcol, destinationcol <= n
    Both the ball and the destination exist in an empty space, and they will not be in the same position initially.
    The maze contains at least 2 empty spaces.


*/

class Solution {
private:
    bool by_bfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& dest) {
        int rows = maze.size();
        int cols = maze[0].size();
        int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));

        std::queue<std::pair<int, int>> q;
        q.push({start[0], start[1]});
        visited[start[0]][start[1]] = true;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == dest[0] && c == dest[1]) {
                return true;
            }

            for (int i = 0; i < 4; ++i) {
                int next_r = r;
                int next_c = c;
                while (next_r >= 0 && next_r < rows && 
                            next_c >=0 && next_c < cols && maze[next_r][next_c] == 0) {

                    next_r += dir[i][0];
                    next_c += dir[i][1];
                }

                next_r -= dir[i][0];
                next_c -= dir[i][1];

                if (!visited[next_r][next_c]) {
                    q.push({next_r, next_c});
                    visited[next_r][next_c] = true;
                }
            }
        }

        return false;
    }
    bool dfs(vector<vector<int>>& maze, int& rows, int& cols, vector<int>& dest, 
            std::vector<std::vector<bool>>& visited, int (*dir)[2], int r, int c) {
        if (visited[r][c]) {
            return false;
        }
        
        if (r == dest[0] && c == dest[1]) {
            return true;
        }

        visited[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            int next_r = r;
            int next_c = c;
            while (next_r + dir[i][0] >= 0 && next_r + dir[i][0] < rows && next_c + dir[i][1] >= 0 && 
                        next_c + dir[i][1] < cols && maze[next_r + dir[i][0]][next_c + dir[i][1]] == 0) {
                next_r += dir[i][0];
                next_c += dir[i][1];

                /*  ball would not stop at destination unless a wall after the destination, 
                    therefore, we do not need this condition 
                    
                if (next_r == dest[0] && next_c == dest[1]) {
                    return true;
                }*/
            }

            if (dfs(maze, rows, cols, dest, visited, dir, next_r, next_c)) {
                return true;
            }
        }
        
        return false;
    }
    bool by_dfs(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        int rows = maze.size();
        int cols = maze[0].size();

        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
        int dir[4][2]{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

        return dfs(maze, rows, cols, destination, visited, dir, start[0], start[1]);
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        return by_bfs(maze, start, destination);
        //return by_dfs(maze, start, destination);
    }
};