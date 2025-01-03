/*
There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.

You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.

A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.

Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.

 

Example 1:

Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
Output: 3
Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).

Example 2:

Input: colors = "a", edges = [[0,0]]
Output: -1
Explanation: There is a cycle from 0 to 0.

 

Constraints:

    n == colors.length
    m == edges.length
    1 <= n <= 10^5
    0 <= m <= 10^5
    colors consists of lowercase English letters.
    0 <= aj, bj < n

*/

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        
        int N = colors.size();
        
        std::vector<int> indegree(N);
        std::vector<std::vector<int>> adj(N, std::vector<int>());

        for (auto& v : edges) {
            adj[v[0]].push_back(v[1]);
            ++indegree[v[1]];
        }

        std::queue<int> q;
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<std::vector<int>> count(N, std::vector<int>(26));
        int ans = 0;
        int visited = 0;
        while (!q.empty()) {
            int n = q.front();
            q.pop();

            ans = std::max(ans, ++count[n][colors[n] - 'a']);
            ++visited;

            for (int neighbor : adj[n]) {

                for (int i = 0; i < 26; ++i) {
                    count[neighbor][i] = std::max(count[neighbor][i], count[n][i]);
                }

                --indegree[neighbor];

                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }

        return visited < N ? -1 : ans;
        
    }
};