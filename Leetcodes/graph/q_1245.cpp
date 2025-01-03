/*
The diameter of a tree is the number of edges in the longest path in that tree.

There is an undirected tree of n nodes labeled from 0 to n - 1. You are given a 2D array edges where edges.length == n - 1 and edges[i] = [ai, bi] indicates that there is an undirected edge between nodes ai and bi in the tree.

Return the diameter of the tree.

 

Example 1:

Input: edges = [[0,1],[0,2]]
Output: 2
Explanation: The longest path of the tree is the path 1 - 0 - 2.

Example 2:

Input: edges = [[0,1],[1,2],[2,3],[1,4],[4,5]]
Output: 4
Explanation: The longest path of the tree is the path 3 - 2 - 1 - 4 - 5.

 

Constraints:

    n == edges.length + 1
    1 <= n <= 10^4
    0 <= ai, bi < n
    ai != bi


*/

class Solution {
private:
    int byDFS(vector<vector<int>>& edges) {
        int diameter = 0;
        int N = edges.size();
        std::vector<std::vector<int>> adj(N + 1, std::vector<int>());
        std::vector<bool> visited(N + 1);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        std::function<int(int)> dfs = [&](int node) -> int{

            visited[node] = true;
            int first_dis = 0;
            int second_dis = 0;
            for (int neighbor : adj[node]) {
                int dis = 0;

                if (!visited[neighbor]) {
                    dis = 1 + dfs(neighbor);
                }

                if (dis > first_dis) {
                    second_dis = first_dis;
                    first_dis = dis;
                } else if (dis > second_dis) {
                    second_dis = dis;
                }
            }

            diameter = std::max(diameter, first_dis + second_dis);

            return first_dis;
        };

        dfs(0);

        return diameter;
    }
public:
    int treeDiameter(vector<vector<int>>& edges) {
        return byDFS(edges);
    }
};