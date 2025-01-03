/*
You are given an m x n grid grid of values 0, 1, or 2, where:

    each 0 marks an empty land that you can pass by freely,
    each 1 marks a building that you cannot pass through, and
    each 2 marks an obstacle that you cannot pass through.

You want to build a house on an empty land that reaches all buildings in the shortest total travel distance. You can only move up, down, left, and right.

Return the shortest travel distance for such a house. If it is not possible to build such a house according to the above rules, return -1.

The total travel distance is the sum of the distances between the houses of the friends and the meeting point.

The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|.

 

Example 1:

Input: grid = [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
Output: 7
Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle at (0,2).
The point (1,2) is an ideal empty land to build a house, as the total travel distance of 3+3+1=7 is minimal.
So return 7.

Example 2:

Input: grid = [[1,0]]
Output: 1

Example 3:

Input: grid = [[1]]
Output: -1

 

Constraints:

    m == grid.length
    n == grid[i].length
    1 <= m, n <= 50
    grid[i][j] is either 0, 1, or 2.
    There will be at least one building in the grid.


*/

class Solution {
private:
    int BFS_from_house_optimize(vector<vector<int>>& grid) {
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<int>> totalDistance(rows, std::vector<int>(cols, 0));

        int emptyLandVal = 0;
        int minDis = 250001;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    minDis = 250001;

                    std::queue<std::pair<int, int>> q;
                    q.push({r, c});

                    int steps = 0;

                    while (!q.empty()) {

                        ++steps;
                        int len = q.size();

                        for (int i = 0; i < len; ++i) {
                            std::pair<int, int> p = q.front();
                            q.pop();

                            int r_now = p.first;
                            int c_now = p.second;

                
                            for (auto& dir : dirs) {
                                int r_next = r_now + dir[0];
                                int c_next = c_now + dir[1];

                                if (r_next >= 0 && c_next >= 0 && r_next < rows && c_next < cols && 
                                                                    grid[r_next][c_next] == emptyLandVal) {
                                    
                                    --grid[r_next][c_next];
                                    totalDistance[r_next][c_next] += steps;
                                    q.push({r_next, c_next});

                                    minDis = std::min(minDis, totalDistance[r_next][c_next]);
                                }
                            }
                        }
                    }

                    --emptyLandVal;
                }
            }
        }

        return minDis == 250001 ? -1 : minDis;
    }

    int BFS_from_house(vector<vector<int>>& grid) {

        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int rows = grid.size();
        int cols = grid[0].size();

        int totalHouses = 0;
        
        //store {total_distance, houses_count}
        std::vector<std::vector<std::vector<int>>> distances(rows, std::vector<std::vector<int>>(cols, {0, 0}));

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {

                    ++totalHouses;

                    std::queue<std::pair<int, int>> q;
                    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
                    q.push({r, c});
                    visited[r][c] = true;

                    int steps = 0;

                    while (!q.empty()) {
                        int len = q.size();

                        for (int i = 0; i < len; ++i) {
                            std::pair<int, int> p = q.front();
                            q.pop();

                            int r_now = p.first;
                            int c_now = p.second;

                            if (grid[r_now][c_now] == 0) {
                                distances[r_now][c_now][0] += steps;
                                distances[r_now][c_now][1] += 1;
                            }
                            
                            for (auto& dir : dirs) {
                                int r_next = r_now + dir[0];
                                int c_next = c_now + dir[1];

                                if (r_next >= 0 && c_next >= 0 && r_next < rows && c_next < cols && 
                                                !visited[r_next][c_next] && grid[r_next][c_next] == 0) {
                                    
                                    visited[r_next][c_next] = true;
                                    q.push({r_next, c_next});
                                }
                            }

                        }

                        ++steps;
                    }
                }
            }
        }

        int minDis = 250001;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (distances[r][c][1] == totalHouses) {
                    minDis = std::min(minDis, distances[r][c][0]);
                }
            }
        }

        return minDis == 250001 ? -1 : minDis;
    }

    int totalHomes(vector<vector<int>>& grid, int rows, int cols) {
        int total = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    ++total;
                }
            }
        }

        return total;
    }

    int BFS_from_empty_land(vector<vector<int>>& grid) {
        
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int rows = grid.size();
        int cols = grid[0].size();
        int totalHouses = totalHomes(grid, rows, cols);

        int minDis = 250001;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {

                if (grid[r][c] == 0) {
                    int disSum = 0;
                    int houseSum = 0;
                    int steps = 0;
                    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
                    std::queue<std::pair<int, int>> q;
                    q.push({r, c});
                    visited[r][c] = true;

                    while (!q.empty() && houseSum != totalHouses) {
                        int len = q.size();

                        for (int i = 0; i < len; ++i) {
                            std::pair<int, int> p = q.front();
                            q.pop();

                            int r_now = p.first;
                            int c_now = p.second;

                            if (grid[r_now][c_now] == 1) {
                                disSum += steps;
                                ++houseSum;
                                continue;
                            }

                            for (auto& dir : dirs) {
                                int r_next = r_now + dir[0];
                                int c_next = c_now + dir[1];

                                if (r_next >= 0 && c_next >= 0 && r_next < rows && c_next < cols && 
                                                !visited[r_next][c_next] && grid[r_next][c_next] != 2) {
                                    
                                    visited[r_next][c_next] = true;
                                    q.push({r_next, c_next});
                                }
                            }
                        }

                        ++steps;
                    }

                    if (houseSum != totalHouses) {
                        for (int r1 = 0; r1 < rows; ++r1) {
                            for (int c1 = 0; c1 < cols; ++c1) {
                                if (grid[r1][c1] == 0 && visited[r1][c1]) {
                                    grid[r1][c1] = 2;
                                }
                            }
                        }

                        disSum = 250001;
                    }

                    minDis = std::min(minDis, disSum);
                }
            }
        }

        return minDis == 250001 ? -1 : minDis;
    }

public:
    int shortestDistance(vector<vector<int>>& grid) {
        
        //return BFS_from_empty_land(grid);
        //return BFS_from_house(grid);
        return BFS_from_house_optimize(grid);
    }
};