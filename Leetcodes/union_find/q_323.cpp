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
    int find_root(int x, std::vector<int>& root) {
        if (x != root[x]) {
            return root[x] = find_root(root[x], root);
        }

        return x;
    }

    void union_set(int x, int y, std::vector<int>& root, std::vector<int>& rank, int& cnt) {
        int rX = find_root(x, root);
        int rY = find_root(y, root);

        if (rX == rY) {
            return;
        }

        //union them if they have different root, so we reduce cnt for every set(1 node 1 set)
        --cnt;

        if (rank[rX] > rank[rY]) {
            root[rY] = rX;

        } else if (rank[rX] < rank[rY]) {
            root[rX] = rY;

        } else {
            root[rY] = rX;
            ++rank[rX];
        }
    }

    int byDSA(int n, vector<vector<int>>& edges) {
        std::vector<int> root(n);
        std::iota(root.begin(), root.end(), 0);
        std::vector<int> rank(n, 1);

        int cnt = n;
        for (auto& e : edges) {
            union_set(e[0], e[1], root, rank, cnt);
        }

        return cnt;
    }
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        return byDSA(n, edges);
    }
};