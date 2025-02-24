/*
You have a graph of n nodes labeled from 0 to n - 1. You are given an integer n and a list of edges where edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the graph.

Return true if the edges of the given graph make up a valid tree, and false otherwise.

 

Example 1:

Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true

Example 2:

Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false

 

Constraints:

    1 <= n <= 2000
    0 <= edges.length <= 5000
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    There are no self-loops or repeated edges.


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

        bool union_set(int x, int y) {
            int px = find(x);
            int py = find(y);

            if (px == py) {
                return false;
            }

            if (rank[px] > rank[py]) {
                parent[py] = px;

            } else if (rank[px] < rank[py]) {
                parent[px] = py;

            } else {
                parent[py] = px;
                rank[py] += 1;
            }

            return true;
        }
    };
    bool by_union_find(int& n, vector<vector<int>>& edges) {
        if (n == 1) {
            return true;
        }

        if (edges.size() != n - 1) {
            return false;
        }

        Union_find uf(n);

        for (int i = 0; i < edges.size(); ++i) {

            if (!uf.union_set(edges[i][0], edges[i][1])) {
                return false;
            }
        }

        return true;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        return by_union_find(n, edges);
    }
};