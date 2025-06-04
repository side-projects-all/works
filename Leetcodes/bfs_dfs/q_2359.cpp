/*
You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.

The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from i, then edges[i] == -1.

You are also given two integers node1 and node2.

Return the index of the node that can be reached from both node1 and node2, such that the maximum between the distance from node1 to that node, and from node2 to that node is minimized. If there are multiple answers, return the node with the smallest index, and if no possible answer exists, return -1.

Note that edges may contain cycles.

 

Example 1:

Input: edges = [2,2,3,-1], node1 = 0, node2 = 1
Output: 2
Explanation: The distance from node 0 to node 2 is 1, and the distance from node 1 to node 2 is 1.
The maximum of those two distances is 1. It can be proven that we cannot get a node with a smaller maximum distance than 1, so we return node 2.

Example 2:

Input: edges = [1,2,-1], node1 = 0, node2 = 2
Output: 2
Explanation: The distance from node 0 to node 2 is 2, and the distance from node 2 to itself is 0.
The maximum of those two distances is 2. It can be proven that we cannot get a node with a smaller maximum distance than 2, so we return node 2.

 

Constraints:

    n == edges.length
    2 <= n <= 10^5
    -1 <= edges[i] < n
    edges[i] != i
    0 <= node1, node2 < n


*/

class Solution {
private:
    void bfs(int& begin, int& n, std::vector<int>& edges, std::vector<int>& dist) {
        std::queue<int> q;
        q.push(begin);

        std::vector<bool> visited(n);
        dist[begin] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (visited[node]) {
                continue;
            }

            visited[node] = true;
            int nei = edges[node];
            if (nei != -1 && !visited[nei]) {
                dist[nei] = 1 + dist[node];
                q.push(nei);
            }
        }
    }
    int by_bfs(vector<int>& edges, int& node1, int& node2) {
        int n = edges.size();

        std::vector<int> dist1(n, INT_MAX);
        std::vector<int> dist2(n, INT_MAX);

        bfs(node1, n, edges, dist1);
        bfs(node2, n, edges, dist2);

        int min_dist_node = -1;
        int curr_min_dist = INT_MAX;
        for (int node = 0; node < n; ++node) {
            if (curr_min_dist > std::max(dist1[node], dist2[node])) {
                min_dist_node = node;
                curr_min_dist = std::max(dist1[node], dist2[node]);
            }
        }

        return min_dist_node;
    }
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        return by_bfs(edges, node1, node2);
    }
};