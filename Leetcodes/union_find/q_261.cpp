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
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        //initialize root and rank
        root = std::vector<int>(n);
        rank = std::vector<int>(n, 1);

        for (int i = 0; i < n; ++i) {
            root[i] = i;
        }

        if (edges.size() != n - 1) {
            return false;
        }

        int p01 = 0;
        int p02 = 0;
        for (auto edge : edges) {
            p01 = edge[0];
            p02 = edge[1];

            if (!unionSet(p01, p02)) {
                return false;
            }
        }


        return true;
    }

private:
    std::vector<int> root;
    std::vector<int> rank;

    int find(int index) {
        //using loop to path compression!!!
        int root_index = index;
        //find root first!!
        while (root[root_index] != root_index) {
            root_index = root[root_index];
        }
        
        //traverse from x, and set value as root_index every node on the path 
        int oldRoot = -1;
        while (index != root_index) {
            oldRoot = root[index];
            root[index] = root_index;
            index = oldRoot;
        }
        
        return root_index;
    }

    bool unionSet(int x, int y) {
        //still big O(N)
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) {
            return false;
        }

        if (rank[rootX] > rank[rootY]) {
            root[rootY] = rootX;
            
        } else if (rank[rootX] < rank[rootY]) {
            root[rootX] = rootY;
            
        } else {
            root[rootY] = rootX;
            rank[rootX] += 1;
        }

        return true;
    }
};