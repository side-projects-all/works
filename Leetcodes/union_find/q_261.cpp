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
    void dfs(std::vector<std::vector<int>>& adj, std::unordered_set<int>& visited, int node) {
        if (visited.find(node) != visited.end()) {
            return;
        }

        visited.insert(node);
        for (int& n : adj[node]) {
            dfs(adj, visited, n);
        }
    }
    bool by_dfs(int& n, vector<vector<int>>& edges) {
        if (edges.size() != n - 1) {
            return false;
        }

        std::unordered_set<int> visited;
        std::vector<std::vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        dfs(adj, visited, 0);
        
        return visited.size() == n;
    }

    std::vector<int> parents;
    std::vector<int> ranks;
    int find(int x) {
        if (parents[x] == -1) {
            return x;
        }

        return parents[x] = find(parents[x]);
    }

    bool union_set(int x, int y) {
        int rx = find(x);
        int ry = find(y);

        if (rx == ry) {
            return false;
        }

        if (ranks[rx] > ranks[ry]) {
            parents[ry] = rx;
            ranks[rx] += 1;

        } else {
            parents[rx] = ry;
            ranks[ry] += 1;
        }

        return true;
    }

    bool by_union_find(int& n, vector<vector<int>>& edges) {
        parents.resize(n, -1);
        ranks.resize(n, 1);

        if (edges.size() != n - 1) {
            return false;
        }

        for (auto& e : edges) {
            if (!union_set(e[0], e[1])) {
                return false;
            }
        }

        return true;
    }
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        //return by_union_find(n, edges);
        return by_dfs(n, edges);
    }
};