/*
Alice and Bob have an undirected graph of n nodes and three types of edges:

    Type 1: Can be traversed by Alice only.
    Type 2: Can be traversed by Bob only.
    Type 3: Can be traversed by both Alice and Bob.

Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.

Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.

 

Example 1:

Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
Output: 2
Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.

Example 2:

Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,4],[2,1,4]]
Output: 0
Explanation: Notice that removing any edge will not make the graph fully traversable by Alice and Bob.

Example 3:

Input: n = 4, edges = [[3,2,3],[1,1,2],[2,3,4]]
Output: -1
Explanation: In the current graph, Alice cannot reach node 4 from the other nodes. Likewise, Bob cannot reach 1. Therefore it's impossible to make the graph fully traversable.

 

 

Constraints:

    1 <= n <= 105
    1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
    edges[i].length == 3
    1 <= typei <= 3
    1 <= ui < vi <= n
    All tuples (typei, ui, vi) are distinct.


*/

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int edges;
public:
    UnionFind(int n) {
        edges = n - 1;
        parent.resize(n + 1);
        rank.resize(n + 1);
        
        //node from 1 to n
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find_parent(int x) {
        if (parent[x] == x) {
            return x;
        }

        return parent[x] = find_parent(parent[x]);
    }

    int union_nodes(int x, int y) {
        x = find_parent(x);
        y = find_parent(y);

        if (x == y) {
            return 0;
        }

        if (rank[x] > rank[y]) {
            rank[x] += rank[y];
            parent[y] = x;

        } else {
            rank[y] += rank[x];
            parent[x] = y;
        }

        --edges;

        return 1;
    }

    bool is_conn() {
        return edges == 0;
    }
};


class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        UnionFind alice(n);
        UnionFind bob(n);

        int bi_edge = 0;
        for (const auto& e : edges) {
            if (e[0] == 3) {
                bi_edge += (alice.union_nodes(e[1], e[2]) | bob.union_nodes(e[1], e[2]));
            }
        }

        for (const auto& e : edges) {
            if (e[0] == 1) {
                bi_edge += alice.union_nodes(e[1], e[2]);
            } else if (e[0] == 2) {
                bi_edge += bob.union_nodes(e[1], e[2]);
            }
        }

        if (alice.is_conn() && bob.is_conn()) {
            return edges.size() - bi_edge;
        }

        return -1;
    }
};