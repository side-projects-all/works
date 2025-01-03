/*

*/

class Solution {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int count;

    int unionFind(vector<vector<char>>& grid) {
        count = 0;

        int rows = grid.size();
        int cols = grid[0].size();        

        if (rows == 0) {
            return 0;
        }
        
        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    parent.push_back(r * cols + c);
                    ++count;
                } else {
                    parent.push_back(-1);
                    
                }

                rank.push_back(0);
            }
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    grid[r][c] = '0';

                    //union with neighbor if they were land
                    if (r - 1 >= 0 && grid[r - 1][c] == '1') {
                        unionSet(r * cols + c, (r - 1) * cols + c);
                    }
                    if (r + 1 < rows && grid[r + 1][c] == '1') {
                        unionSet(r * cols + c, (r + 1) * cols + c);
                    } 
                    if (c - 1 >= 0 && grid[r][c - 1] == '1') {
                        unionSet(r * cols + c, r * cols + c - 1);
                    }
                    if (c + 1 < cols && grid[r][c + 1] == '1') {
                        unionSet(r * cols + c, r * cols + c + 1);
                    } 
                }
            }
        }

        return getCnt();
    }

    int find(int i) {

        if (parent[i] != i) {
            parent[i] = find(parent[i]);
        }

        return parent[i];
    }

    void unionSet(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX] += 1;
            }

            --count;
        }
    }

    int getCnt() const {
        return count;
    }

    int dfs(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int islands = 0;
        
        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        std::stack<std::pair<int, int>> s;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == '1') {
                    ++islands;

                    s.push({r, c});
                    grid[r][c] = '0';

                    while (!s.empty()) {
                        std::pair<int, int> node = s.top();
                        s.pop();

                        int nowR = node.first;
                        int nowC = node.second;

                        for (const auto& p : directions) {

                            int nextR = nowR + p.first;
                            int nextC = nowC + p.second;
                            if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols && 
                                                                            grid[nextR][nextC] == '1') {

                                s.push({nextR, nextC});
                                grid[nextR][nextC] = '0';
                            }
                        }

                    }

                }
            }
        }

        return islands;
    }

    int bfs(vector<vector<char>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int islands = 0;

        std::pair<int, int> directions[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

        std::queue<std::pair<int, int>> q;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                
                //if we find a land, we start to bfs, after the bfs, we add 1 to islands
                if (grid[r][c] == '1') {

                    ++islands;
                    
                    q.push({r, c});
                    grid[r][c] = '0';

                    while (!q.empty()) {

                        std::pair<int, int> node = q.front();
                        q.pop();
                        int nowR = node.first;
                        int nowC = node.second;

                        for (const auto& p : directions) {

                            int nextR = nowR + p.first;
                            int nextC = nowC + p.second;
                            if (nextR >= 0 && nextR < rows && nextC >= 0 && nextC < cols && 
                                                                            grid[nextR][nextC] == '1') {

                                q.push({nextR, nextC});
                                grid[nextR][nextC] = '0';
                            }
                        }
                    }
                }                
            }
        }

        return islands;
    }

public:
    int numIslands(vector<vector<char>>& grid) {
        //return bfs(grid);
        //return dfs(grid);
        return unionFind(grid);
    }
};