/*
You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads, where roads[i] = [ai, bi, costi] indicates that there is a bidirectional road between cities ai and bi with a cost of traveling equal to costi.

You can buy apples in any city you want, but some cities have different costs to buy apples. You are given the 1-based array appleCost where appleCost[i] is the cost of buying one apple from city i.

You start at some city, traverse through various roads, and eventually buy exactly one apple from any city. After you buy that apple, you have to return back to the city you started at, but now the cost of all the roads will be multiplied by a given factor k.

Given the integer k, return a 1-based array answer of size n where answer[i] is the minimum total cost to buy an apple if you start at city i.

 

Example 1:

Input: n = 4, roads = [[1,2,4],[2,3,2],[2,4,5],[3,4,1],[1,3,4]], appleCost = [56,42,102,301], k = 2
Output: [54,42,48,51]
Explanation: The minimum cost for each starting city is the following:
- Starting at city 1: You take the path 1 -> 2, buy an apple at city 2, and finally take the path 2 -> 1. The total cost is 4 + 42 + 4 * 2 = 54.
- Starting at city 2: You directly buy an apple at city 2. The total cost is 42.
- Starting at city 3: You take the path 3 -> 2, buy an apple at city 2, and finally take the path 2 -> 3. The total cost is 2 + 42 + 2 * 2 = 48.
- Starting at city 4: You take the path 4 -> 3 -> 2 then you buy at city 2, and finally take the path 2 -> 3 -> 4. The total cost is 1 + 2 + 42 + 1 * 2 + 2 * 2 = 51.

Example 2:

Input: n = 3, roads = [[1,2,5],[2,3,1],[3,1,2]], appleCost = [2,3,1], k = 3
Output: [2,3,1]
Explanation: It is always optimal to buy the apple in the starting city.

 

Constraints:

    2 <= n <= 1000
    1 <= roads.length <= 1000
    1 <= ai, bi <= n
    ai != bi
    1 <= costi <= 10^5
    appleCost.length == n
    1 <= appleCost[i] <= 10^5
    1 <= k <= 100
    There are no repeated edges.


*/

class Solution {
private:
    std::vector<long long> shortest_path(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        //build adjacent list
        std::vector<std::vector<std::pair<int, int>>> adj(n, std::vector<std::pair<int, int>>());
        for (const auto& r : roads) {
            adj[r[0] - 1].push_back({r[1] - 1, r[2]});
            adj[r[1] - 1].push_back({r[0] - 1, r[2]});
        }

        std::vector<long long> ans(appleCost.begin(), appleCost.end());

        std::function<void()> byDijstra = [&]() {

            std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
            
            for (int i = 0; i < n; ++i) {
                pq.push({appleCost[i], i});
            }
            
            while (!pq.empty()) {
                const auto [curr_total_cost, curr] = pq.top();
                pq.pop();

                if (ans[curr] < curr_total_cost) {
                    continue;
                }

                for (const auto& [nei, nei_cost] : adj[curr]) {
                    int to_nei_cost = ans[curr] + (k + 1) * nei_cost;

                    if (to_nei_cost < ans[nei]) {
                        ans[nei] = to_nei_cost;
                        pq.push({ans[nei], nei});
                    }
                }
            }
        };

        byDijstra();

        return ans;
    }
public:
    vector<long long> minCost(int n, vector<vector<int>>& roads, vector<int>& appleCost, int k) {
        return shortest_path(n, roads, appleCost, k);
    }
};