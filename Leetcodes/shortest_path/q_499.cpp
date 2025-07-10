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

struct State {
    int dist;
    std::string path;
    int r;
    int c;

    State(int d, std::string p, int i, int j) : dist{d}, path{p}, r{i}, c{j} {}

    bool operator<(const State& s2) const {
        if (dist == s2.dist) {
            return path > s2.path;
        }

        return dist > s2.dist;
    }
};

class Solution {
private:
    std::string by_dijkstra(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        int rows = maze.size();
        int cols = maze[0].size();
        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INT_MAX));
        std::vector<std::vector<std::string>> path(rows, std::vector<std::string>(cols, ""));

        std::priority_queue<State> pq;
        pq.emplace(0, "", ball[0], ball[1]);
        dist[ball[0]][ball[1]] = 0;

        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //u, d, l, r
        char dir_ch[4] = {'u', 'd', 'l', 'r'};

        while (!pq.empty()) {
            State curr = pq.top();
            pq.pop();

            if (curr.r == hole[0] && curr.c == hole[1]) {
                return curr.path;
            }

            if (curr.dist > dist[curr.r][curr.c] || 
                    (curr.dist == dist[curr.r][curr.c] && curr.path > path[curr.r][curr.c])) {
                continue;
            }

            for (int i = 0; i < 4; ++i) {
                int next_r = curr.r;
                int next_c = curr.c;
                int steps = 0;

                while (next_r + dir[i][0] >= 0 && next_r + dir[i][0] < rows && 
                        next_c + dir[i][1] >= 0 && next_c + dir[i][1] < cols && 
                                maze[next_r + dir[i][0]][next_c + dir[i][1]] == 0) {

                    next_r += dir[i][0];
                    next_c += dir[i][1];
                    ++steps;

                    if (next_r == hole[0] && next_c == hole[1]) {
                        break;
                    }
                }

                int next_dist = curr.dist + steps;
                std::string next_path = curr.path + dir_ch[i];

                if (next_dist < dist[next_r][next_c] || 
                    (next_dist == dist[next_r][next_c] && next_path < path[next_r][next_c])) {

                    dist[next_r][next_c] = next_dist;
                    path[next_r][next_c] = next_path;

                    pq.emplace(next_dist, next_path, next_r, next_c);
                }
            }
        }

        return "impossible";
    }
public:
    string findShortestWay(vector<vector<int>>& maze, vector<int>& ball, vector<int>& hole) {
        return by_dijkstra(maze, ball, hole);
    }
};