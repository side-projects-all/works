/*
There is an undirected connected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.

You are given the integer n and the array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.

Return an array answer of length n where answer[i] is the sum of the distances between the ith node in the tree and all other nodes.

 

Example 1:

Input: n = 6, edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]
Output: [8,12,6,10,10,10]
Explanation: The tree is shown above.
We can see that dist(0,1) + dist(0,2) + dist(0,3) + dist(0,4) + dist(0,5)
equals 1 + 1 + 2 + 2 + 2 = 8.
Hence, answer[0] = 8, and so on.

Example 2:

Input: n = 1, edges = []
Output: [0]

Example 3:

Input: n = 2, edges = [[1,0]]
Output: [1,1]

 

Constraints:

    1 <= n <= 3 * 10^4
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    ai != bi
    The given input represents a valid tree.


*/

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        std::vector<int> ans(n);
        std::vector<int> cnt(n, 1);
        std::vector<std::vector<int>> graph(n, std::vector<int>());

        for (const auto e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }

        std::function<void(int, int)> dfs = [&](int node, int p) {
            for (int c : graph[node]) {
                if (c != p) {
                    dfs(c, node);
                    cnt[node] += cnt[c];
                    ans[node] += ans[c] + cnt[c];
                }
            }
        };
        std::function<void(int, int)> dfs2 = [&](int node, int p) {
            for (int c : graph[node]) {
                if (c != p) {
                    ans[c] = ans[node] - cnt[c] + n - cnt[c];
                    dfs2(c, node);
                }
            }
        };

        dfs(0, -1);
        dfs2(0, -1);

        return ans;
    }
};