/*
You are given an undirected weighted connected graph containing n nodes labeled from 0 to n - 1, and an integer array edges where edges[i] = [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight wi.

Some edges have a weight of -1 (wi = -1), while others have a positive weight (wi > 0).

Your task is to modify all edges with a weight of -1 by assigning them positive integer values in the range [1, 2 * 109] so that the shortest distance between the nodes source and destination becomes equal to an integer target. If there are multiple modifications that make the shortest distance between source and destination equal to target, any of them will be considered correct.

Return an array containing all edges (even unmodified ones) in any order if it is possible to make the shortest distance from source to destination equal to target, or an empty array if it's impossible.

Note: You are not allowed to modify the weights of edges with initial positive weights.

 

Example 1:

Input: n = 5, edges = [[4,1,-1],[2,0,-1],[0,3,-1],[4,3,-1]], source = 0, destination = 1, target = 5
Output: [[4,1,1],[2,0,1],[0,3,3],[4,3,1]]
Explanation: The graph above shows a possible modification to the edges, making the distance from 0 to 1 equal to 5.

Example 2:

Input: n = 3, edges = [[0,1,-1],[0,2,5]], source = 0, destination = 2, target = 6
Output: []
Explanation: The graph above contains the initial edges. It is not possible to make the distance from 0 to 2 equal to 6 by modifying the edge with weight -1. So, an empty array is returned.

Example 3:

Input: n = 4, edges = [[1,0,4],[1,2,3],[2,3,5],[0,3,-1]], source = 0, destination = 2, target = 6
Output: [[1,0,4],[1,2,3],[2,3,5],[0,3,1]]
Explanation: The graph above shows a modified graph having the shortest distance from 0 to 2 as 6.

 

Constraints:

    1 <= n <= 100
    1 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 3
    0 <= ai, bi < n
    wi = -1 or 1 <= wi <= 10^7
    ai != bi
    0 <= source, destination < n
    source != destination
    1 <= target <= 10^9
    The graph is connected, and there are no self-loops or repeated edges


*/

class Solution {
public:
    vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
        //return by_traditional_dijkstra(n, edges, source, destination, target);
        return by_pq_dijkstra(n, edges, source, destination, target);
    }

private:
    
    vector<vector<int>> by_pq_dijkstra(int n, vector<vector<int>>& edges, int source, int destination, int target) {

        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            if (e[2] != -1) {
                adj[e[0]].emplace_back(e[1], e[2]);
                adj[e[1]].emplace_back(e[0], e[2]);
            }
        }

        int curr_shortest_path = pq_dijkstra(n, source, destination, adj);

        if (curr_shortest_path < target) {
            return std::vector<std::vector<int>>{};
        }

        bool matches_target = (curr_shortest_path == target);

        for (auto& e : edges) {
            if (e[2] > 0) {
                continue;
            }

            e[2] = matches_target ? 2e9 : 1;
            adj[e[0]].emplace_back(e[1], e[2]);
            adj[e[1]].emplace_back(e[0], e[2]);

            if (!matches_target) {
                int new_dis = pq_dijkstra(n, source, destination, adj);

                if (new_dis <= target) {
                    matches_target = true;
                    e[2] += target - new_dis;
                }
            }
        }

        return matches_target ? edges : std::vector<std::vector<int>>{};
        
    }
    long long pq_dijkstra(int n, int src, int dest, const vector<vector<pair<int, int>>>& adj) {
        std::vector<int> min_dis(n, 2e9);
        std::vector<bool> visited(n);

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

        min_dis[src] = 0;
        pq.emplace(0, src);

        while (!pq.empty()) {
            auto [d, u] = pq.top(); //distance, unvisited node
            pq.pop();

            if (d > min_dis[u]) {
                continue;
            }

            for (const auto& [v, weight] : adj[u]) {

                if (d + weight < min_dis[v]) {
                    min_dis[v] = d + weight;
                    pq.emplace(min_dis[v], v);
                }
            }
        }

        return min_dis[dest];
    }

    vector<vector<int>> by_traditional_dijkstra(int n, vector<vector<int>>& edges, int source, int destination, int target) {

        long long curr_shortest_path = traditional_dijkstra(edges, n, source, destination);

        if (curr_shortest_path < target) {
            return std::vector<std::vector<int>>{};
        }

        bool matches_target = (curr_shortest_path == target);

        for (auto& e : edges) {
            if (e[2] > 0) {
                continue;
            }

            e[2] = matches_target ? 2e9 : 1;

            if (!matches_target) {
                long long new_dis = traditional_dijkstra(edges, n, source, destination);

                if (new_dis <= target) {
                    matches_target = true;
                    e[2] += target - new_dis;
                }
            }
        }

        return matches_target ? edges : std::vector<std::vector<int>>{};
    }
    long long traditional_dijkstra(const vector<vector<int>>& edges, int nodes, int src, int dest) {

        std::vector<std::vector<long long>> adj(nodes, std::vector<long long>(nodes, 2e9));
        std::vector<bool> visited(nodes);
        std::vector<long long> mis_dis(nodes, 2e9);

        mis_dis[src] = 0;

        for (const auto& e : edges) {
            if (e[2] != -1) {
                adj[e[0]][e[1]] = e[2];
                adj[e[1]][e[0]] = e[2];
            }
        }

        for (int i = 0; i < nodes; ++i) {
            int nearest_unvisited = -1;

            for (int j = 0; j < nodes; ++j) {
                if (!visited[j] && (nearest_unvisited == -1 || mis_dis[j] < mis_dis[nearest_unvisited])) {
                    nearest_unvisited = j;
                }
            }

            visited[nearest_unvisited] = true;

            for (int v = 0; v < nodes; ++v) {
                mis_dis[v] = std::min(mis_dis[v], mis_dis[nearest_unvisited] + adj[nearest_unvisited][v]);
            }
        }

        return mis_dis[dest];
    }
};