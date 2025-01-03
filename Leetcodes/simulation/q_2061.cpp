/*
A room is represented by a 0-indexed 2D binary matrix room where a 0 represents an empty space and a 1 represents a space with an object. The top left corner of the room will be empty in all test cases.

A cleaning robot starts at the top left corner of the room and is facing right. The robot will continue heading straight until it reaches the edge of the room or it hits an object, after which it will turn 90 degrees clockwise and repeat this process. The starting space and all spaces that the robot visits are cleaned by it.

Return the number of clean spaces in the room if the robot runs indefinetely.

 

Example 1:

 

Input: room = [[0,0,0],[1,1,0],[0,0,0]]

Output: 7

Explanation:

    ​​​​​​​The robot cleans the spaces at (0, 0), (0, 1), and (0, 2).
    The robot is at the edge of the room, so it turns 90 degrees clockwise and now faces down.
    The robot cleans the spaces at (1, 2), and (2, 2).
    The robot is at the edge of the room, so it turns 90 degrees clockwise and now faces left.
    The robot cleans the spaces at (2, 1), and (2, 0).
    The robot has cleaned all 7 empty spaces, so return 7.

Example 2:

 

Input: room = [[0,1,0],[1,0,0],[0,0,0]]

Output: 1

Explanation:

    The robot cleans the space at (0, 0).
    The robot hits an object, so it turns 90 degrees clockwise and now faces down.
    The robot hits an object, so it turns 90 degrees clockwise and now faces left.
    The robot is at the edge of the room, so it turns 90 degrees clockwise and now faces up.
    The robot is at the edge of the room, so it turns 90 degrees clockwise and now faces right.
    The robot is back at its starting position.
    The robot has cleaned 1 space, so return 1.

Example 3:

Input: room = [[0,0,0],[0,0,0],[0,0,0]]

Output: 8​​​​​​​

 

 

Constraints:

    m == room.length
    n == room[r].length
    1 <= m, n <= 300
    room[r][c] is either 0 or 1.
    room[0][0] == 0


*/

class Solution {
public:
    int numberOfCleanRooms(vector<vector<int>>& room) {
        int rows = room.size();
        int cols = room[0].size();

        //corner case
        if (rows == 1 && cols == 1) {
            return 1;
        }
        //only one column
        if (rows > 1 && cols == 1) {

            if (room[1][0] == 1) {
                return 1;
            } else {
                int cnt = 1;
                int i = 1;
                while (i < rows && room[i][0] != 1) {
                    ++i;
                }

                return i;
            }
            
        }
        //only one row
        if (cols > 1 && rows == 1) {

            if (room[0][1] == 1) {
                return 1;
            } else {
                int cnt = 1;
                int i = 1;
                while (i < cols && room[0][i] != 1) {
                    ++i;
                }

                return i;
            }
        }
        //block around room[0][0]
        if (room[0][1] == 1 && room[1][0] == 1) {
            return 1;
        }

        //row, col; clockwise; right, down, left, up
        int dirs[4][2]{ {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; 
        std::vector<std::vector<int>> visited(rows, std::vector<int>(cols, 0));
        int cleaned = 0;

        std::queue<std::tuple<int, int, int>> q;
        q.push({0, 0, 0});

        while (!q.empty()) {
            const auto [r, c, dir] = q.front();
            q.pop();

            if (visited[r][c] == 0) {
                ++cleaned;
            }

            visited[r][c] |= 1 << dir;

            //four directions
            for (int d = 0; d < 4; ++d) {
                int next_d = (dir + d) % 4;
                int next_r = r + dirs[next_d][0];
                int next_c = c + dirs[next_d][1];

                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols && 
                    room[next_r][next_c] == 0) {
                    
                    if (visited[next_r][next_c] >> next_d & 1) {
                        return cleaned;
                    } else {
                        q.push({next_r, next_c, next_d});
                        break;
                    }
                }
            }
        }

        return cleaned;
    }
};