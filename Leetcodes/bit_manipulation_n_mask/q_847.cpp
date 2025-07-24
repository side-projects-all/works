/*
You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.

Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.

 

Example 1:

Input: graph = [[1,2,3],[0],[0],[0]]
Output: 4
Explanation: One possible path is [1,0,2,0,3]

Example 2:

Input: graph = [[1],[0,2,4],[1,3,4],[2],[1,2]]
Output: 4
Explanation: One possible path is [0,1,4,2,3]

 

Constraints:

    n == graph.length
    1 <= n <= 12
    0 <= graph[i].length < n
    graph[i] does not contain i.
    If graph[a] contains b, then graph[b] contains a.
    The input graph is always connected.


*/

class Solution {
private:
    int recurrsive(vector<vector<int>>& graph) {
        int N = graph.size();
        int totalMask = (1 << N) - 1;
        std::vector<std::vector<int>> mem(N + 1, std::vector<int>(totalMask + 1, -1));

        std::function<int(int, int)> recurr = [&](int node, int mask) -> int {
            
            //base case
            if ((mask & (mask - 1)) == 0) {
                return 0;
            }

            if (mem[node][mask] != -1) {
                return mem[node][mask];
            }
            
            mem[node][mask] = INT_MAX - 1;
            for (int nei : graph[node]) {

                if ((mask & (1 << nei)) != 0) {
                    int visited = recurr(nei, mask);
                    int not_visited = recurr(nei, mask ^ (1 << node));
                    int min = std::min(visited, not_visited);
                    mem[node][mask] = std::min(mem[node][mask], 1 + min);
                }
            }

            return mem[node][mask];
        };

        int shortest = INT_MAX;
        for (int n = 0; n < N; ++n) {
            shortest = std::min(shortest, recurr(n, totalMask));
        }

        return shortest;
    }

public:
    int shortestPathLength(vector<vector<int>>& graph) {
        return recurrsive(graph);
    }
};