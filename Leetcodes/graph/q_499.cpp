/*
There is a ball in a maze with empty spaces (represented as 0) and walls (represented as 1). The ball can go through the empty spaces by rolling up, down, left or right, but it won't stop rolling until hitting a wall. When the ball stops, it could choose the next direction. There is also a hole in this maze. The ball will drop into the hole if it rolls onto the hole.

Given the m x n maze, the ball's position ball and the hole's position hole, where ball = [ballrow, ballcol] and hole = [holerow, holecol], return a string instructions of all the instructions that the ball should follow to drop in the hole with the shortest distance possible. If there are multiple valid instructions, return the lexicographically minimum one. If the ball can't drop in the hole, return "impossible".

If there is a way for the ball to drop in the hole, the answer instructions should contain the characters 'u' (i.e., up), 'd' (i.e., down), 'l' (i.e., left), and 'r' (i.e., right).

The distance is the number of empty spaces traveled by the ball from the start position (excluded) to the destination (included).

You may assume that the borders of the maze are all walls (see examples).

 

Example 1:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], ball = [4,3], hole = [0,1]
Output: "lul"
Explanation: There are two shortest ways for the ball to drop into the hole.
The first way is left -> up -> left, represented by "lul".
The second way is up -> left, represented by 'ul'.
Both ways have shortest distance 6, but the first way is lexicographically smaller because 'l' < 'u'. So the output is "lul".

Example 2:

Input: maze = [[0,0,0,0,0],[1,1,0,0,1],[0,0,0,0,0],[0,1,0,0,1],[0,1,0,0,0]], ball = [4,3], hole = [3,0]
Output: "impossible"
Explanation: The ball cannot reach the hole.

Example 3:

Input: maze = [[0,0,0,0,0,0,0],[0,0,1,0,0,1,0],[0,0,0,0,1,0,0],[0,0,0,0,0,0,1]], ball = [0,4], hole = [3,5]
Output: "dldr"

 

Constraints:

    m == maze.length
    n == maze[i].length
    1 <= m, n <= 100
    maze[i][j] is 0 or 1.
    ball.length == 2
    hole.length == 2
    0 <= ballrow, holerow <= m
    0 <= ballcol, holecol <= n
    Both the ball and the hole exist in an empty space, and they will not be in the same position initially.
    The maze contains at least 2 empty spaces.


*/

class Solution {
private:
    struct State {
        int row;
        int col;
        int dist;
        std::string path;
    };

    struct My_comparator {

        bool operator() (const State& s1, const State& s2) {
            if (s1.dist == s2.dist) {
                return s1.path > s2.path;
            }

            return s1.dist > s2.dist;
        }
    };

    std::string byDijkstra(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        std::vector<std::vector<int>> dir{ {0, -1},  {-1, 0}, {0, 1}, {1, 0} };
        std::vector<std::string> textDir{ "l", "u", "r", "d" };

        int rows = maze.size();
        int cols = maze[0].size();

        std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
        std::priority_queue<State, std::vector<State>, My_comparator> pq;

        pq.push({ball[0], ball[1], 0, ""});

        while (!pq.empty()) {
            State s = pq.top();
            pq.pop();
            int r_now = s.row;
            int c_now = s.col;

            if (visited[r_now][c_now]) {
                continue;
            }

            if (r_now == hole[0] && c_now == hole[1]) {
                return s.path;
            }

            visited[r_now][c_now] = true;

            for (int i = 0; i < 4; ++i) {

                int next_r = r_now + dir[i][0];
                int next_c = c_now + dir[i][1];
                std::string txt_dir = textDir[i];

                int dist = 0;

                while (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && maze[next_r][next_c] == 0) {
                    
                    if (next_r == hole[0] && next_c == hole[1]) {
                        break;
                    }

                    next_r += dir[i][0];
                    next_c += dir[i][1];
                    ++dist;
                }

                if (next_r != hole[0] || next_c != hole[1]) {
                    next_r -= dir[i][0];
                    next_c -= dir[i][1];
                }
                
                pq.push({next_r, next_c, s.dist + dist, s.path + txt_dir});
            }

        }

        return "impossible";
    }
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        return byDijkstra(maze, ball, hole);
    }
};