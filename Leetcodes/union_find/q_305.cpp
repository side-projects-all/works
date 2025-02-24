/*
You are given an empty 2D binary grid grid of size m x n. The grid represents a map where 0's represent water and 1's represent land. Initially, all the cells of grid are water cells (i.e., all the cells are 0's).

We may perform an add land operation which turns the water at position into a land. You are given an array positions where positions[i] = [ri, ci] is the position (ri, ci) at which we should operate the ith operation.

Return an array of integers answer where answer[i] is the number of islands after turning the cell (ri, ci) into a land.

An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 

Example 1:

Input: m = 3, n = 3, positions = [[0,0],[0,1],[1,2],[2,1]]
Output: [1,1,2,3]
Explanation:
Initially, the 2d grid is filled with water.
- Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land. We have 1 island.
- Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land. We still have 1 island.
- Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land. We have 2 islands.
- Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land. We have 3 islands.

Example 2:

Input: m = 1, n = 1, positions = [[0,0]]
Output: [1]

 

Constraints:

    1 <= m, n, positions.length <= 10^4
    1 <= m * n <= 10^4
    positions[i].length == 2
    0 <= ri < m
    0 <= ci < n

*/

class Solution {
private:
    class Union_find {
    public:
        std::vector<int> parent;
        std::vector<int> rank;

        Union_find(const int& n) {
            parent.resize(n, -1);
            rank.resize(n, 1);
        }

        int find(int x) {
            if (parent[x] == x) {
                return x;
            }

            return parent[x] = find(parent[x]);
        }

        void union_set(int x, int y, int& cnt) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return;
            }
            if (rank[px] > rank[py]) {
                parent[py] = px;

            } else if (rank[py] > rank[px]) {
                parent[px] = py;

            } else {
                parent[py] = px;
                rank[px] += 1;
            }

            --cnt;
        }
    };
    
    std::vector<int> by_union_find(int& m, int& n, vector<vector<int>>& positions) {
        Union_find uf(m * n);
        int cnt = 0;
        int len = positions.size();

        std::vector<int> ans(len);
        for (int i = 0; i < len; ++i) {
            int pos = positions[i][0] * n + positions[i][1];

            //already appeared
            if (uf.parent[pos] != -1) {
                ans[i] = cnt;
                continue;
            }

            uf.parent[pos] = pos;
            ++cnt;

            if (positions[i][0] - 1 >= 0 && uf.parent[(positions[i][0] - 1) * n + positions[i][1]] != -1) {
                uf.union_set(pos, (positions[i][0] - 1) * n + positions[i][1], cnt);
            }

            if (positions[i][0] + 1 < m && uf.parent[(positions[i][0] + 1) * n + positions[i][1]] != -1) {
                uf.union_set(pos, (positions[i][0] + 1) * n + positions[i][1], cnt);
            }

            if (positions[i][1] - 1 >= 0 && uf.parent[positions[i][0] * n + (positions[i][1] - 1)] != -1) {
                uf.union_set(pos, positions[i][0] * n + (positions[i][1] - 1), cnt);
            }

            if (positions[i][1] + 1 < n && uf.parent[positions[i][0] * n + (positions[i][1] + 1)] != -1) {
                uf.union_set(pos, positions[i][0] * n + (positions[i][1] + 1), cnt);
            }

            ans[i] = cnt;
        }

        return ans;
    }
public:
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        return by_union_find(m, n, positions);
    }
};