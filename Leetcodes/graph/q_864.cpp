/*
You are given an m x n grid grid where:

    '.' is an empty cell.
    '#' is a wall.
    '@' is the starting point.
    Lowercase letters represent keys.
    Uppercase letters represent locks.

You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.

If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.

For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.

Return the lowest number of moves to acquire all keys. If it is impossible, return -1.

 

Example 1:

Input: grid = ["@.a..","###.#","b.A.B"]
Output: 8
Explanation: Note that the goal is to obtain all the keys not to open all the locks.

Example 2:

Input: grid = ["@..aA","..B#.","....b"]
Output: 6

Example 3:

Input: grid = ["@Aa"]
Output: -1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 30
    grid[i][j] is either an English letter, '.', '#', or '@'. 
    There is exactly one '@' in the grid.
    The number of keys in the grid is in the range [1, 6].
    Each key in the grid is unique.
    Each key in the grid has a matching lock.


*/

struct my_hash {
    template<class T1, class T2>
    size_t operator() (const std::pair<T1, T2>& p) const {
        return p.first ^ p.second;
    }
};

class Solution {
private:
    int bfs(vector<string>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        std::queue<std::vector<int>> q;

        std::unordered_map<int, std::unordered_set<std::pair<int, int>, my_hash>> seen;
        std::unordered_set<char> keySet;
        std::unordered_set<char> lockSet;

        int allKeys = 0;

        int startR = -1;
        int startC = -1;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                char cell = grid[r][c];

                if (cell >= 'a' && cell <= 'z') {
                    allKeys += (1 << (cell - 'a'));
                    keySet.insert(cell);
                }

                if (cell >= 'A' && cell <= 'Z') {
                    lockSet.insert(cell);
                }

                if (cell == '@') {
                    startR = r;
                    startC = c;
                }
            }
        }

        //the vector contains: [row, column, key state, distance]
        q.push({startR, startC, 0, 0});

        //already visited starting point
        seen[0].insert({startR, startC});

        while (!q.empty()) {
            std::vector<int> node = q.front();
            q.pop();

            int currR = node[0];
            int currC = node[1];
            int keys = node[2];
            int dist = node[3];

            for (const auto& p : directions) {
                int nextR = currR + p.first;
                int nextC = currC + p.second;

                //not wall '#' and in the valid range
                if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols && grid[nextR][nextC] != '#') {

                    char cell = grid[nextR][nextC];

                    //if this is a key
                    if (keySet.find(cell) != keySet.end()) {

                        //check if already collected this key
                        if (((1 << (cell - 'a')) & keys) != 0) {
                            continue;
                        }

                        //not visited, collect this key
                        int newKeys = (keys | (1 << (cell - 'a')));

                        //check if we already collect all keys
                        if (newKeys == allKeys) {
                            return dist + 1;
                        }

                        seen[newKeys].insert({nextR, nextC});
                        q.push({nextR, nextC, newKeys, dist + 1});
                    }

                    //if this were a lock and we did not have key, continue to go other directions
                    if (lockSet.find(cell) != lockSet.end() && ((keys & (1 << (cell - 'A'))) == 0)) {
                        continue;
                    } 
                    
                    //if this were just another cell without key and lock and had not visited yet
                    if (seen[keys].find({nextR, nextC}) == seen[keys].end()) {
                        
                        seen[keys].insert({nextR, nextC});
                        q.push({nextR, nextC, keys, dist + 1});
                    }
                }
            }
        }

        return -1;
    }
public:
    int shortestPathAllKeys(vector<string>& grid) {
        return bfs(grid);
    }
};