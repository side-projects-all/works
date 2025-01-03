/*
A series of highways connect n cities numbered from 0 to n - 1. You are given a 2D integer array highways where highways[i] = [city1i, city2i, tolli] indicates that there is a highway that connects city1i and city2i, allowing a car to go from city1i to city2i and vice versa for a cost of tolli.

You are also given an integer discounts which represents the number of discounts you have. You can use a discount to travel across the ith highway for a cost of tolli / 2 (integer division). Each discount may only be used once, and you can only use at most one discount per highway.

Return the minimum total cost to go from city 0 to city n - 1, or -1 if it is not possible to go from city 0 to city n - 1.

 

Example 1:

Input: n = 5, highways = [[0,1,4],[2,1,3],[1,4,11],[3,2,3],[3,4,2]], discounts = 1
Output: 9
Explanation:
Go from 0 to 1 for a cost of 4.
Go from 1 to 4 and use a discount for a cost of 11 / 2 = 5.
The minimum cost to go from 0 to 4 is 4 + 5 = 9.

Example 2:

Input: n = 4, highways = [[1,3,17],[1,2,7],[3,2,5],[0,1,6],[3,0,20]], discounts = 20
Output: 8
Explanation:
Go from 0 to 1 and use a discount for a cost of 6 / 2 = 3.
Go from 1 to 2 and use a discount for a cost of 7 / 2 = 3.
Go from 2 to 3 and use a discount for a cost of 5 / 2 = 2.
The minimum cost to go from 0 to 3 is 3 + 3 + 2 = 8.

Example 3:

Input: n = 4, highways = [[0,1,3],[2,3,2]], discounts = 0
Output: -1
Explanation:
It is impossible to go from 0 to 3 so return -1.

 

Constraints:

    2 <= n <= 1000
    1 <= highways.length <= 1000
    highways[i].length == 3
    0 <= city1i, city2i <= n - 1
    city1i != city2i
    0 <= tolli <= 10^5
    0 <= discounts <= 500
    There are no duplicate highways.


*/

class Solution {
private:
    int by_space_optimized_dijkstra(int& n, vector<vector<int>>& highways, int& discounts) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int i = 0; i < highways.size(); ++i) {
            int u = highways[i][0];
            int v = highways[i][1];
            int toll = highways[i][2];

            adj[u].push_back({v, toll});
            adj[v].push_back({u, toll});
        }

        std::priority_queue<std::tuple<int, int, int>, 
                            std::vector<std::tuple<int, int, int>>, 
                            std::greater<std::tuple<int, int, int>>> pq;

        pq.push({0, 0, 0});

        std::vector<std::vector<int>> dist(n, std::vector<int>(discounts + 1, INT_MAX));
        dist[0][0] = 0;

        //std::vector<std::vector<bool>> visited(n, std::vector<bool>(discounts + 1, false));

        while (!pq.empty()) {
            auto [curr_cost, city, discounts_used] = pq.top();
            pq.pop();

            /*
            if (visited[city][discounts_used]) {
                continue;
            }
            */

            if (curr_cost > dist[city][discounts_used]) {
                continue;
            }

            for (int i = 0; i < adj[city].size(); ++i) {
                int nei = adj[city][i].first;
                int toll = adj[city][i].second;

                //move to neighbor without using a discount
                if (curr_cost + toll < dist[nei][discounts_used]) {
                    dist[nei][discounts_used] = curr_cost + toll;
                    pq.push({dist[nei][discounts_used], nei, discounts_used});
                }

                //move to the neighbor using a discount if available
                if (discounts_used < discounts) {
                    int discounted_cost = curr_cost + toll / 2;

                    if (discounted_cost < dist[nei][discounts_used + 1]) {
                        dist[nei][discounts_used + 1] = discounted_cost;

                        pq.push({discounted_cost, nei, discounts_used + 1});
                    }
                }
            }
        }

        int min_cost = *std::min_element(dist[n - 1].begin(), dist[n - 1].end());

        return min_cost == INT_MAX ? -1 : min_cost;
    }
    int by_dijkstra(int& n, vector<vector<int>>& highways, int& discounts) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);
        for (int i = 0; i < highways.size(); ++i) {
            int u = highways[i][0];
            int v = highways[i][1];
            int toll = highways[i][2];

            adj[u].push_back({v, toll});
            adj[v].push_back({u, toll});
        }

        std::priority_queue<std::tuple<int, int, int>, 
                            std::vector<std::tuple<int, int, int>>, 
                            std::greater<std::tuple<int, int, int>>> pq;

        pq.push({0, 0, 0});

        std::vector<std::vector<int>> dist(n, std::vector<int>(discounts + 1, INT_MAX));
        dist[0][0] = 0;

        std::vector<std::vector<bool>> visited(n, std::vector<bool>(discounts + 1, false));

        while (!pq.empty()) {
            auto [curr_cost, city, discounts_used] = pq.top();
            pq.pop();

            if (visited[city][discounts_used]) {
                continue;
            }

            for (int i = 0; i < adj[city].size(); ++i) {
                int nei = adj[city][i].first;
                int toll = adj[city][i].second;

                //move to neighbor without using a discount
                if (curr_cost + toll < dist[nei][discounts_used]) {
                    dist[nei][discounts_used] = curr_cost + toll;
                    pq.push({dist[nei][discounts_used], nei, discounts_used});
                }

                //move to the neighbor using a discount if available
                if (discounts_used < discounts) {
                    int discounted_cost = curr_cost + toll / 2;

                    if (discounted_cost < dist[nei][discounts_used + 1]) {
                        dist[nei][discounts_used + 1] = discounted_cost;

                        pq.push({discounted_cost, nei, discounts_used + 1});
                    }
                }
            }
        }

        int min_cost = *std::min_element(dist[n - 1].begin(), dist[n - 1].end());

        return min_cost == INT_MAX ? -1 : min_cost;
    }
public:
    int minimumCost(int n, vector<vector<int>>& highways, int discounts) {
        //return by_dijkstra(n, highways, discounts);
        return by_space_optimized_dijkstra(n, highways, discounts);
    }
};