/*
You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.

You are given two arrays redEdges and blueEdges where:

    redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
    blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.

Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.

 

Example 1:

Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
Output: [0,1,-1]

Example 2:

Input: n = 3, redEdges = [[0,1]], blueEdges = [[2,1]]
Output: [0,1,-1]

 

Constraints:

    1 <= n <= 100
    0 <= redEdges.length, blueEdges.length <= 400
    redEdges[i].length == blueEdges[j].length == 2
    0 <= ai, bi, uj, vj < n


*/

class Solution {
private:
    vector<int> byBFS(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);

        for (auto& r : redEdges) {
            adj[r[0]].push_back({ r[1], 0 });   //{neighbor, color}
        }

        for (auto& b : blueEdges) {
            adj[b[0]].push_back({ b[1], 1 });   //{neighbor, color}
        }

        std::vector<int> ans(n, -1);
        std::vector<std::vector<bool>> visit(n, std::vector<bool>(2));  //visit[node][color]
        std::queue<std::vector<int>> q;

        q.push({0, 0, -1});     //{ node, the number of steps used so far, color of the edge }
        visit[0][0] = true;
        visit[0][1] = true;
        ans[0] = 0;

        while (!q.empty()) {
            std::vector<int> e = q.front();
            int node = e[0];
            int steps = e[1];
            int prevColor = e[2];
            q.pop();

            for (auto& [neighbor, color] : adj[node]) {
                if (!visit[neighbor][color] && color != prevColor) {
                    visit[neighbor][color] = true;
                    q.push({ neighbor, 1 + steps, color });

                    if (ans[neighbor] == -1) {
                        ans[neighbor] = 1 + steps;
                    }
                }
            }
        }

        return ans;
    }
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
        return byBFS(n, redEdges, blueEdges);
    }
};