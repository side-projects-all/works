/*
There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

You want to determine if there is a valid path that exists from vertex source to vertex destination.

Given edges and the integers n, source, and destination, return true if there is a valid path from source to destination, or false otherwise.

 

Example 1:

Input: n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
Output: true
Explanation: There are two paths from vertex 0 to vertex 2:
- 0 → 1 → 2
- 0 → 2

Example 2:

Input: n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0, destination = 5
Output: false
Explanation: There is no path from vertex 0 to vertex 5.

 

Constraints:

    1 <= n <= 2 * 105
    0 <= edges.length <= 2 * 105
    edges[i].length == 2
    0 <= ui, vi <= n - 1
    ui != vi
    0 <= source, destination <= n - 1
    There are no duplicate edges.
    There are no self edges.


*/

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        visited = std::vector<bool>(n, false);
        p_des = destination;
        p_len = n;

        for (int i = 0; i < edges.size(); ++i) {
            int a = edges[i][0];
            int b = edges[i][1];

            p_graph[a].push_back(b);
            p_graph[b].push_back(a);
        }

        //return dfs_recursion(source);
        //return dfs_iterative(source);
        return bfs_iterative(source);
    }

private:
    int p_des;
    std::unordered_map<int, std::vector<int>> p_graph;
    std::vector<bool> visited;
    int p_len;
    

    bool bfs_iterative(int now) {
        std::queue<int> q;

        q.push(now);            //initialize
        visited[now] = true;

        while(!q.empty()) {
            int curr = q.front();
            q.pop();

            //check if found the destination
            if (curr == p_des) {
                return true;
            }

            for (int neighbor : p_graph[curr]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return false;
    }

    bool dfs_recursion(int now) {

        if (now == p_des) {
            return true;
        }

        if (!visited[now]) {
            visited[now] = true;

            for (int i = 0; i < p_graph[now].size(); ++i) {
                int go = p_graph[now][i];

                if (dfs_recursion(go)) {
                    return true;
                }
            }
        }

        return false;
    }

    bool dfs_iterative(int now) {
        std::stack<int> p_stack({now});
        visited[now] = true;

        while(!p_stack.empty()) {
            int curr = p_stack.top();
            p_stack.pop();

            if (curr == p_des) {
                return true;
            }

            for (int i = 0; i < p_graph[curr].size(); ++i) {
                int next = p_graph[curr][i];

                if (!visited[next]) {
                    visited[next] = true;

                    p_stack.push(next);
                }
            }
        }

        return false;
    }
};