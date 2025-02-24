/*
You have a graph of n nodes. You are given an integer n and an array edges where edges[i] = [ai, bi] indicates that there is an edge between ai and bi in the graph.

Return the number of connected components in the graph.

 

Example 1:

Input: n = 5, edges = [[0,1],[1,2],[3,4]]
Output: 2

Example 2:

Input: n = 5, edges = [[0,1],[1,2],[2,3],[3,4]]
Output: 1

 

Constraints:

    1 <= n <= 2000
    1 <= edges.length <= 5000
    edges[i].length == 2
    0 <= ai <= bi < n
    ai != bi
    There are no repeated edges.


*/

class Solution {
private:
    class Union_find {
    private:
        std::vector<int> parent;
        std::vector<int> rank;
    public:
        Union_find(const int& n) {
            parent.resize(n);
            rank.resize(n, 1);

            for (int i = 0; i < n; ++i) {
                parent[i] = i;
            }
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

            if (px ==py) {
                return;
            }

            if (rank[px] > rank[py]) {
                parent[py] = px;

            } else if (rank[px] < rank[py]) {
                parent[px] = py;

            } else {
                parent[px] = py;
                rank[py] += 1;
            }

            --cnt;
        }
    };
    int by_union_find(int& n, vector<vector<int>>& edges) {
        Union_find uf(n);
        int cnt = n;

        for (int i = 0; i < edges.size(); ++i) {
            uf.union_set(edges[i][0], edges[i][1], cnt);
        }

        return cnt;
    }
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        return by_union_find(n, edges);
    }
};