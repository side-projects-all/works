/*
There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

 

Example 1:
Illustration of graph

Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:

Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.

 

Constraints:

    n == graph.length
    1 <= n <= 10^4
    0 <= graph[i].length <= n
    0 <= graph[i][j] <= n - 1
    graph[i] is sorted in a strictly increasing order.
    The graph may contain self-loops.
    The number of edges in the graph will be in the range [1, 4 * 10^4].


*/

class Solution {
private:
    bool dfs(int node, vector<vector<int>>& adj, std::vector<bool>& visited, std::vector<bool>& in_stack) {
        if (in_stack[node]) {
            return true;
        }

        if (visited[node]) {
            return false;
        }

        visited[node] = true;
        in_stack[node] = true;

        for (auto& nei : adj[node]) {
            if (dfs(nei, adj, visited, in_stack)) {
                return true;
            }
        }

        in_stack[node] = false;
        return false;
    }
    vector<int> by_dfs(vector<vector<int>>& graph) {
        int n = graph.size();
        std::vector<bool> visited(n);
        std::vector<bool> in_stack(n);

        for (int i = 0; i < n; ++i) {
            dfs(i, graph, visited, in_stack);
        }

        std::vector<int> safe_nodes;
        for (int i = 0; i < n; ++i) {
            if (!in_stack[i]) {
                safe_nodes.push_back(i);
            }
        }

        return safe_nodes;
    }
    vector<int> by_topological_sort(vector<vector<int>>& graph) {
        int n = graph.size();
        if (n == 1) {
            return {0};
        }

        std::vector<std::vector<int>> rev_adj(n, std::vector<int>());
        std::vector<int> indegree(n);
        for (int from = 0; from < n; ++from) {
            for (int to = 0; to < graph[from].size(); ++to) {
                rev_adj[graph[from][to]].push_back(from);
                ++indegree[from];
            }
        }

        std::queue<int> q;
        for (int i = 0; i < indegree.size(); ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        std::vector<bool> safe_nodes(n);
        std::vector<int> ans;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            safe_nodes[node] = true;
            ans.push_back(node);

            for (int& nei : rev_adj[node]) {
                --indegree[nei];

                if (indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        std::sort(ans.begin(), ans.end());
        return ans;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        //return by_topological_sort(graph);
        return by_dfs(graph);
    }
};