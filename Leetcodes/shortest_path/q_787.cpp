/*
There are n cities connected by some number of flights. You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from city fromi to city toi with cost pricei.

You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.

 

Example 1:

Input: n = 4, flights = [[0,1,100],[1,2,100],[2,0,100],[1,3,600],[2,3,200]], src = 0, dst = 3, k = 1
Output: 700
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 3 is marked in red and has cost 100 + 600 = 700.
Note that the path through cities [0,1,2,3] is cheaper but is invalid because it uses 2 stops.

Example 2:

Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 1
Output: 200
Explanation:
The graph is shown above.
The optimal path with at most 1 stop from city 0 to 2 is marked in red and has cost 100 + 100 = 200.

Example 3:

Input: n = 3, flights = [[0,1,100],[1,2,100],[0,2,500]], src = 0, dst = 2, k = 0
Output: 500
Explanation:
The graph is shown above.
The optimal path with no stops from city 0 to 2 is marked in red and has cost 500.

 

Constraints:

    1 <= n <= 100
    0 <= flights.length <= (n * (n - 1) / 2)
    flights[i].length == 3
    0 <= fromi, toi < n
    fromi != toi
    1 <= pricei <= 104
    There will not be any multiple flights between two cities.
    0 <= src, dst, k < n
    src != dst


*/

class Solution {
private:
    int byBellmanFord(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        //space optimize
        std::vector<int> curr(n, INT_MAX);
        std::vector<int> prev(n, INT_MAX);
        prev[src] = 0;

        //m: means at most edge 
        for (int m = 1; m < k + 2; ++m) {
            curr[src] = 0;
            for (int i = 0; i < flights.size(); ++i) {

                int flight_from = flights[i][0];
                int flight_now = flights[i][1];
                int price = flights[i][2];

                if (prev[flight_from] < INT_MAX) {
                    curr[flight_now] = std::min(curr[flight_now], prev[flight_from] + price);
                }
            }

            prev.assign(curr.begin(), curr.end());
        }
        
        return curr[dst] == INT_MAX ? -1 : curr[dst];
        
        
        /*
        std::vector<int> dist(n, std::numeric_limits<int>::max());
        dist[src] = 0;

        //using edges as outer for-loop, it just likes the tabulation in dynamic programming
        //this k + 1 equals the max edges could be used
        for (int i = 0; i <= k; ++i) {

            //this is the second array used for storing results of last k stop
            std::vector<int> tmp(dist);
            for (const auto& flight : flights) {

                int t_src = flight[0];
                int t_dst = flight[1];
                int cost = flight[2];
                if (dist[t_src] != std::numeric_limits<int>::max()) {
                    tmp[t_dst] = std::min(tmp[t_dst], dist[t_src] + cost);
                }
            }

            dist = tmp;
        }

        return (dist[dst] == std::numeric_limits<int>::max()) ? -1 : dist[dst];
        */
    }

    int byDijkstra(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (auto edge : flights) {
            int t_src = edge[0];
            int t_dst = edge[1];
            int t_cost = edge[2];
            adj[t_src].push_back(std::make_pair(t_dst, t_cost));
        }
        
        std::vector<int> stops(n, std::numeric_limits<int>::max());
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;

        pq.push({0, src, 0});

        while (!pq.empty()) {
            auto tmp = pq.top();
            pq.pop();
            int dist = tmp[0];
            int node = tmp[1];
            int steps = tmp[2];
            //this is for the requirement k
            if (steps > stops[node] || steps > k + 1) {
                continue;
            }

            stops[node] = steps;
            //why return dist is workable?
            //because we will push this adjacent node with update information, 
            //we could have newest cost from source to destination
            if (node == dst) {
                return dist;
            }

            for (auto &[neighbor, price] : adj[node]) {
                pq.push({dist + price, neighbor, steps + 1});
            }
        }

        return -1;
    }
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //corner case
        if (src == dst) {
            return 0;
        }

        return byBellmanFord(n, flights, src, dst, k);
        //return byDijkstra(n, flights, src, dst, k);
    }
};