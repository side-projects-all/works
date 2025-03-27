/*
You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.

You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.

Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.

 

Example 1:

Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output: 4
Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
The four ways to get there in 7 minutes are:
- 0 ➝ 6
- 0 ➝ 4 ➝ 6
- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

Example 2:

Input: n = 2, roads = [[1,0,10]]
Output: 1
Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.

 

Constraints:

    1 <= n <= 200
    n - 1 <= roads.length <= n * (n - 1) / 2
    roads[i].length == 3
    0 <= ui, vi <= n - 1
    1 <= timei <= 10^9
    ui != vi
    There is at most one road connecting any two intersections.
    You can reach any intersection from any other intersection.


*/

class Solution {
private:
    int by_dijkstra_alg(int& n, vector<vector<int>>& roads) {
        std::vector<std::vector<std::pair<int, int>>> adj(n);

        for (int i = 0; i < roads.size(); ++i) {
            adj[roads[i][0]].push_back({roads[i][1], roads[i][2]}); //u to {v, time}
            adj[roads[i][1]].push_back({roads[i][0], roads[i][2]}); //v to {u, time}
        }

        std::vector<long> shotest_times(n, LONG_MAX);
        shotest_times[0] = 0;
        std::vector<int> shortest_cnt(n);
        shortest_cnt[0] = 1;

        std::priority_queue<std::pair<long, int>, std::vector<std::pair<long, int>>, std::greater<std::pair<long, int>>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto [time_now, now] = pq.top();
            pq.pop();

            if (time_now > shotest_times[now]) {
                continue;
            }

            for (auto& [nei, time_to_nei] : adj[now]) {

                if (time_now + time_to_nei < shotest_times[nei]) {
                    shotest_times[nei] = time_now + time_to_nei;       //update times to neighbor
                    shortest_cnt[nei] = shortest_cnt[now];        //update the cnt of shortest paths to neighbor from now
                    pq.push({shotest_times[nei], nei});

                } else if (time_now + time_to_nei == shotest_times[nei]) {
                    shortest_cnt[nei] = (shortest_cnt[nei] + shortest_cnt[now]) % 1'000'000'007;
                }
            }
        }

        return shortest_cnt[n - 1];
    }
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        return by_dijkstra_alg(n, roads);
    }
};