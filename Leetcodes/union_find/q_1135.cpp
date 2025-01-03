/*
There are n cities labeled from 1 to n. You are given the integer n and an array connections where connections[i] = [xi, yi, costi] indicates that the cost of connecting city xi and city yi (bidirectional connection) is costi.

Return the minimum cost to connect all the n cities such that there is at least one path between each pair of cities. If it is impossible to connect all the n cities, return -1,

The cost is the sum of the connections' costs used.

 

Example 1:

Input: n = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
Output: 6
Explanation: Choosing any 2 edges will connect all cities so we choose the minimum 2.

Example 2:

Input: n = 4, connections = [[1,2,3],[3,4,4]]
Output: -1
Explanation: There is no way to connect all cities even if all edges are used.

 

Constraints:

    1 <= n <= 10^4
    1 <= connections.length <= 10^4
    connections[i].length == 3
    1 <= xi, yi <= n
    xi != yi
    0 <= costi <= 10^5


*/

class Solution {
private:
    struct my_comparator {
        bool operator() (const std::vector<int>& v1, const std::vector<int>& v2) const {
            return v1[2] < v2[2];
        }
    };

    int byPrim(int n, vector<vector<int>>& connections) {
        
        std::vector<std::vector<std::pair<int,int>>> adj(n + 1);
        for (int i = 0; i < connections.size(); ++i) {
            int p1 = connections[i][0];
            int p2 = connections[i][1];
            int cost = connections[i][2];

            adj[p1].push_back({cost, p2});
            adj[p2].push_back({cost, p1});
        }

        std::vector<bool> visited(n + 1);
        std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, 
                                                    std::greater<std::pair<int,int>>> pq;

        pq.push({0, 1});    //visit the first point, and the cost is zero!!
        int total = 0;
        int cnt = n;

        while (!pq.empty() && cnt > 0) {
            std::pair<int,int> p = pq.top();
            pq.pop();

            int cost = p.first;
            int p2 = p.second;
            
            if (!visited[p2]) {
                visited[p2] = true;
                total += cost;

                for (const auto& p : adj[p2]) {
                     if (!visited[p.second]) {
                         pq.push(p);
                     }
                }

                --cnt;
            }
        }

        return (cnt == 0) ? total : -1;
    }

    int find_root(int x, std::vector<int>& root) {
        if (root[x] != x) {
            root[x] = find_root(root[x], root);
        }

        return root[x];
    }

    bool union_set(int x, int y, std::vector<int>& root, std::vector<int>& rank) {
        int rX = find_root(x, root);
        int rY = find_root(y, root);

        //already in the same set, add this edge will form cycle
        if (rX == rY) {
            return false;
        }

        if (rank[rX] > rank[rY]) {
            root[rY] = rX;

        } else if (rank[rX] > rank[rY]) {
            root[rX] = rY;

        } else {
            rank[rX] += 1;
            root[rY] = rX;
        }

        return true;
    }
    int byKruskal(int n, vector<vector<int>>& connections) {
        std::sort(connections.begin(), connections.end(), my_comparator());

        std::vector<int> root(n + 1, 0);
        std::iota(root.begin(), root.end(), 0);
        std::vector<int> rank(n + 1, 1);

        int total = 0;
        int edgeUsed = 0;

        for (int i = 0; i < connections.size() && edgeUsed < n - 1; ++i) {
            int x = connections[i][0];
            int y = connections[i][1];
            int cost = connections[i][2];

            if (union_set(x, y, root, rank)) {
                total += cost;
                ++edgeUsed;
            }
        }

        return edgeUsed == n - 1 ? total : -1;
    }

public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        //return byKruskal(n, connections);
        return byPrim(n, connections);
    }
};