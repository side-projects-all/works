/*
You are given an integer n and a 2D integer array queries.

There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.

Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.

 

Example 1:

Input: n = 5, queries = [[2,4],[0,2],[0,4]]

Output: [3,2,1]

Explanation:

After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.

After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.

After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.

Example 2:

Input: n = 4, queries = [[0,3],[0,2]]

Output: [1,1]

Explanation:

After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.

After the addition of the road from 0 to 2, the length of the shortest path remains 1.

 

Constraints:

    3 <= n <= 500
    1 <= queries.length <= 500
    queries[i].length == 2
    0 <= queries[i][0] < queries[i][1] < n
    1 < queries[i][1] - queries[i][0]
    There are no repeated roads among the queries.


*/

class Solution {
private:
    int find_min_dis(std::vector<std::vector<int>> &adj, int& n) {

        std::vector<int> dp(n);
    
        //from the second last node down to the first node
        for (int curr = n - 2; curr >= 0; --curr) {

            int min_dis = n;
            //bfs from neighbors to find the minimum distance
            for (auto nei : adj[curr]) {
                min_dis = std::min(min_dis, dp[nei] + 1);
            }
            dp[curr] = min_dis;  //update min_dis
        }

        return dp[0];
    }

public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>> &queries) {
        std::vector<int> ans;
        std::vector<std::vector<int>> adj(n, std::vector<int>());

        for (int i = 0; i < n - 1; i++) {
            adj[i].push_back(i + 1);
        }

        // add new edges for each query
        for (auto &road : queries) {
            int u = road[0];
            int v = road[1];
            adj[u].push_back(v);

            //find the minimum distance after adding the new edge
            ans.push_back(find_min_dis(adj, n));
        }
        return ans;
    }
};