/*
There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

 

Example 1:

Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.

Example 2:

Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.

 

Constraints:

    2 <= n <= 100
    1 <= edges.length <= n * (n - 1) / 2
    edges[i].length == 3
    0 <= fromi < toi < n
    1 <= weighti, distanceThreshold <= 10^4
    All pairs (fromi, toi) are distinct.


*/

class Solution {
private:
    /*
    std::vector<std::vector<std::pair<int, int>>> adj;
    void build_adj_list(int n, std::vector<std::vector<int>>& edges, std::vector<std::vector<std::pair<int, int>>>& adj) {

        adj = std::vector<std::vector<std::pair<int, int>>>(n);
        for (int i = 0; i < edges.size(); ++i) {
            int b = edges[i][0];
            int e = edges[i][1];
            int w = edges[i][2];

            adj[b].emplace_back(e, w);
            adj[e].emplace_back(b, w);
        }
    }*/

    int find_fewest(int n, std::vector<std::vector<int>>& paths, int distanceThreshold) {
        int ans = -1;
        int fewest = n;

        for (int i = 0; i < n; ++i) {
            int reachable_cnt = 0;

            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }

                if (paths[i][j] <= distanceThreshold) {
                    ++reachable_cnt;
                }
            }

            if (reachable_cnt <= fewest) {
                fewest = reachable_cnt;
                ans = i;
            }
        }

        return ans;
    }
    /*
    void dijkstra(int n, std::vector<int>& shortest_path, int s) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                                                    std::greater<std::pair<int, int>>> pq;

        pq.emplace(0, s);
        std::fill(shortest_path.begin(), shortest_path.end(), INT_MAX);
        shortest_path[s] = 0;

        while (!pq.empty()) {
            auto [nei_dis, nei_city] = pq.top();
            pq.pop();

            if (nei_dis > shortest_path[nei_city]) {
                continue;
            }

            for (const auto& [next_city, distance] : adj[nei_city]) {

                if (shortest_path[next_city] > nei_dis + distance) {
                    shortest_path[next_city] = nei_dis + distance;

                    pq.emplace(shortest_path[next_city], next_city);
                }
            }
        }

    }
    int by_dijkstra(int n, int distanceThreshold) {
        std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n));

        for (int i = 0; i < n; ++i) {
            dijkstra(n, shortest_paths[i], i);
        }

        //find fewest reachable
        return find_fewest(n, shortest_paths, distanceThreshold);
    }
    */

    void bellman_ford(int n, std::vector<int>& shortest_path, int s, vector<vector<int>>& edges) {
        std::fill(shortest_path.begin(), shortest_path.end(), INT_MAX);
        shortest_path[s] = 0;

        for (int i = 1; i < n; ++i) {
            for (const auto& edge : edges) {
                int b = edge[0];
                int e = edge[1];
                int w = edge[2];

                if (shortest_path[b] != INT_MAX && shortest_path[b] + w < shortest_path[e]) {
                    shortest_path[e] = shortest_path[b] + w;
                }

                if (shortest_path[e] != INT_MAX && shortest_path[e] + w < shortest_path[b]) {
                    shortest_path[b] = shortest_path[e] + w;
                }
            }
        }

    }
    int by_bellman_ford(int n, int distanceThreshold, vector<vector<int>>& edges) {
        std::vector<std::vector<int>> shortest_paths(n, std::vector<int>(n));
        
        for (int i = 0; i < n; ++i) {
            bellman_ford(n, shortest_paths[i], i, edges);
        }

        //find fewest reachable
        return find_fewest(n, shortest_paths, distanceThreshold);
    }

    int by_floyd_warshall(int n, int distanceThreshold, vector<vector<int>>& edges) {
        std::vector<std::vector<int>> distance(n, std::vector<int>(n, INT_MAX));

        for (int i = 0; i < n; ++i) {
            distance[i][i] = 0;
        }

        for (const auto& edge : edges) {
            int b = edge[0];
            int e = edge[1];
            int w = edge[2];

            distance[b][e] = w;
            distance[e][b] = w;
        }

        //mid should be at outest loop!!
        for (int mid = 0; mid < n; ++mid) {
            for (int begin = 0; begin < n; ++begin) {
                for (int end = 0; end < n; ++end) {
                
                    int by_mid = (distance[begin][mid] == INT_MAX || distance[mid][end] == INT_MAX) ? 
                                                    INT_MAX : distance[begin][mid] + distance[mid][end];
                    distance[begin][end] = std::min(distance[begin][end], by_mid);
                }
            }
        }

        return find_fewest(n, distance, distanceThreshold);
    }
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        //build_adj_list(n, edges, adj);

        //return by_dijkstra(n, distanceThreshold);
        //return by_bellman_ford(n, distanceThreshold, edges);
        return by_floyd_warshall(n, distanceThreshold, edges);
    }
};