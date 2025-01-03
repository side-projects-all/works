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
    bool dfs(vector<vector<int>>& maze, int r, int c, vector<int>& destination, 
                std::vector<std::vector<int>>& dir, std::vector<std::vector<bool>>& visited) {

        if (visited[r][c]) {
            return false;
        }

        if (r == destination[0] && c == destination[1]) {
            return true;
        }

        visited[r][c] = true;
        int rows = maze.size();
        int cols = maze[0].size();

        for (int i = 0; i < dir.size(); ++i) {
            int move_r = r;
            int move_c = c;
            while (move_r >= 0 && move_r < rows && 
                        move_c >=0 && move_c < cols && maze[move_r][move_c] == 0) {

                move_r += dir[i][0];
                move_c += dir[i][1];
            }

            if (dfs(maze, move_r - dir[i][0], move_c - dir[i][1], destination, dir, visited)) {
                return true;
            }
        }

        return false;
    }

    bool bfs(vector<vector<int>>& maze, int r, int c, vector<int>& destination, 
                std::vector<std::vector<int>>& dir, std::vector<std::vector<bool>>& visited) {
        
        int rows = maze.size();
        int cols = maze[0].size();
        std::queue<std::pair<int, int>> q;
        q.push({r, c});
        visited[r][c] = true;

        while (!q.empty()) {
            int curr_r = q.front().first;
            int curr_c = q.front().second;
            q.pop();

            if (curr_r == destination[0] && curr_c == destination[1]) {
                return true;
            }

            for (int i = 0; i < dir.size(); ++i) {
                int move_r = curr_r;
                int move_c = curr_c;
                while (move_r >= 0 && move_r < rows && 
                            move_c >=0 && move_c < cols && maze[move_r][move_c] == 0) {

                    move_r += dir[i][0];
                    move_c += dir[i][1];
                }

                move_r -= dir[i][0];
                move_c -= dir[i][1];

                if (!visited[move_r][move_c]) {
                    q.push({move_r, move_c});
                    visited[move_r][move_c] = true;
                }
            }
        }

        return false;
    }
public:
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        //direction[i][0]: row, direction[i][1]: col
        std::vector<std::vector<int>> dir{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
        std::vector<std::vector<bool>> visited(maze.size(), std::vector<bool>(maze[0].size()));

        //return dfs(maze, start[0], start[1], destination, dir, visited);
        return bfs(maze, start[0], start[1], destination, dir, visited);
    }
};