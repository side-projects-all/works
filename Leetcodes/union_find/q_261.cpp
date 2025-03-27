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
    std::vector<int> parent;
    std::vector<int> rank;
    int find(int x) {
        if (parent[x] == -1) {
            return x;
        }

        return parent[x] = find(parent[x]);
    }

    bool union_set(int x, int y) {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry) {
            return false;
        }

        if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
            rank[rx] += rank[ry];

        } else {
            parent[rx] = ry;
            rank[ry] += rank[rx];
        }

        return true;
    }
    bool by_union_find(int& n, vector<vector<int>>& edges) {
        parent.resize(n, -1);
        rank.resize(n, 1);

        if (edges.size() != n - 1) {
            return false;
        }

        for (int i = 0; i < edges.size(); ++i) {
            if (!union_set(edges[i][0], edges[i][1])) {
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