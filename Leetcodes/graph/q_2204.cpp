/*
You are given a positive integer n representing the number of nodes in a connected undirected graph containing exactly one cycle. The nodes are numbered from 0 to n - 1 (inclusive).

You are also given a 2D integer array edges, where edges[i] = [node1i, node2i] denotes that there is a bidirectional edge connecting node1i and node2i in the graph.

The distance between two nodes a and b is defined to be the minimum number of edges that are needed to go from a to b.

Return an integer array answer of size n, where answer[i] is the minimum distance between the ith node and any node in the cycle.

 

Example 1:

Input: n = 7, edges = [[1,2],[2,4],[4,3],[3,1],[0,1],[5,2],[6,5]]
Output: [1,0,0,0,0,1,2]
Explanation:
The nodes 1, 2, 3, and 4 form the cycle.
The distance from 0 to 1 is 1.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 3 is 0.
The distance from 4 to 4 is 0.
The distance from 5 to 2 is 1.
The distance from 6 to 2 is 2.

Example 2:

Input: n = 9, edges = [[0,1],[1,2],[0,2],[2,6],[6,7],[6,8],[0,3],[3,4],[3,5]]
Output: [0,0,0,1,2,2,1,2,2]
Explanation:
The nodes 0, 1, and 2 form the cycle.
The distance from 0 to 0 is 0.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 1 is 1.
The distance from 4 to 1 is 2.
The distance from 5 to 1 is 2.
The distance from 6 to 2 is 1.
The distance from 7 to 2 is 2.
The distance from 8 to 2 is 2.

 

Constraints:

    3 <= n <= 10^5
    edges.length == n
    edges[i].length == 2
    0 <= node1i, node2i <= n - 1
    node1i != node2i
    The graph is connected.
    The graph has exactly one cycle.
    There is at most one edge between any pair of vertices.


*/

class Solution {
private:
    vector<int> by_bfs(int& n, vector<vector<int>>& edges) {
        std::vector<bool> in_cycle(n, true);
        std::vector<bool> visited(n, false);  
        std::vector<int> degree(n);
        std::vector<int> dis(n);
        std::vector<std::vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
            ++degree[e[0]];
            ++degree[e[1]];
        }

        std::queue<int> q;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                q.push(i);
            }
        }

        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            in_cycle[curr] = false;

            for (auto& nei : adj[curr]) {

                --degree[nei];
                if (degree[nei] == 1) {
                    q.push(nei);
                }
            }
        }

        for (int curr = 0; curr < n; ++curr) {

            if (in_cycle[curr]) {
                q.push(curr);
                visited[curr] = true;
            }
        }

        int curr_dis = 0;
        while (!q.empty()) {
            int queueSize = q.size();
                                              
            for (int i = 0; i < queueSize; i++) {
                int curr = q.front();
                q.pop();

                dis[curr] = curr_dis;

                for (auto& nei : adj[curr]) {

                    if (visited[nei]) {
                        continue;
                    }

                    q.push(nei);
                    visited[nei] = true;
                }
            }
            ++curr_dis; 
        }

        return dis;
    }
    void cal_dis(int curr, int curr_dis, std::vector<std::vector<int>>& adj, std::vector<int>& dis, 
                        std::vector<bool>& in_cycle, std::vector<bool>& visited) {

        dis[curr] = curr_dis;
        visited[curr] = true;

        for (auto& nei : adj[curr]) {
            if (visited[nei]) {
                continue;
            }

            int new_dis = in_cycle[nei] ? 0 : curr_dis + 1;
            cal_dis(nei, new_dis, adj, dis, in_cycle, visited);
        }
    }
    bool find_cycle_nodes(int curr, std::vector<std::vector<int>>& adj, std::vector<bool>& in_cycle, 
                            std::vector<bool>& visited, std::vector<int>& parent) {

        visited[curr] = true;
        for (auto& nei : adj[curr]) {

            if (!visited[nei]) {

                parent[nei] = curr;
                if (find_cycle_nodes(nei, adj, in_cycle, visited, parent)) {
                    return true;
                }

            } else if (parent[curr] != nei) {

                in_cycle[nei] = true;
                int tmp = curr;

                while (tmp != nei) {
                    in_cycle[tmp] = true;
                    tmp = parent[tmp];
                }

                return true;
            }
        }

        return false;
    }

    vector<int> by_dfs(int& n, vector<vector<int>>& edges) {
        std::vector<std::vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        std::vector<bool> in_cycle(n);
        std::vector<bool> visited(n);
        std::vector<int> parent(n);
        std::vector<int> dis(n);
        find_cycle_nodes(0, adj, in_cycle, visited, parent);

        std::fill(visited.begin(), visited.end(), false);

        for (int i = 0; i < n; ++i) {
            if (in_cycle[i]) {
                cal_dis(i, 0, adj, dis, in_cycle, visited);
                break;
            }
        }

        return dis;
    }
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        return by_dfs(n, edges);
        //return by_bfs(n, edges);
    }
};
