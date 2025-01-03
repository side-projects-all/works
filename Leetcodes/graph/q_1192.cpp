/*
There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. Any server can reach other servers directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some servers unable to reach some other server.

Return all critical connections in the network in any order.

 

Example 1:

Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.

Example 2:

Input: n = 2, connections = [[0,1]]
Output: [[0,1]]

 

Constraints:

    2 <= n <= 10^5
    n - 1 <= connections.length <= 10^5
    0 <= ai, bi <= n - 1
    ai != bi
    There are no repeated connections.


*/

class Solution {
public:
    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections) {
        
        std::vector<int> adj[n];
        for(int i = 0; i < connections.size(); ++i) {
            adj[connections[i][0]].push_back(connections[i][1]);
            adj[connections[i][1]].push_back(connections[i][0]);
        }

        std::vector<int> time(n, 0);
        std::vector<int> lowestTime(n, 0);
        std::vector<std::vector<int>> bridges;
        std::vector<int> vis(n, 0);

        dfs(0, -1, adj, time, lowestTime, bridges, vis);

        return bridges;
    }
private:
    int timer = 1;
    void dfs(int node, int parent, std::vector<int> adj[], std::vector<int>& time, 
                std::vector<int>& lowestTime, std::vector<vector<int>>& bridges, std::vector<int>& vis) {
        
        vis[node] = 1;
        time[node] = lowestTime[node] = timer;
        ++timer;
        for(auto it : adj[node]) {
            if(it == parent) {
                continue;

            } else if(vis[it] == 0) {

                dfs(it, node, adj, time, lowestTime, bridges, vis);
                lowestTime[node] = std::min(lowestTime[node], lowestTime[it]);

                if(lowestTime[it] > time[node]) {
                    bridges.push_back({it, node});
                }
            } else {
                lowestTime[node] = std::min(lowestTime[node], lowestTime[it]);
            }
        }

    }
};

/*
struct pair_hash {
    template<class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const { //the const here is necessary!!
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second) << 1;

        return h1 ^ h2;  
    }
};

class Solution {
private:
    void editGraph(int n, vector<vector<int>>& connections, 
                            std::unordered_map<int, std::vector<int>>& graph, 
                                std::unordered_map<int, int>& rank, 
                                    std::unordered_map<std::pair<int, int>, bool, pair_hash>& connDict) {

        for (int i = 0; i < n; ++i) {
            rank[i] = 0;
        }

        for (auto& edge : connections) {

            //make undirected graph
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);

            int sortedU = std::min(u, v);
            int sortedV = std::max(u, v);
            std::pair<int, int> key = std::make_pair(sortedU, sortedV);
            connDict.insert(std::make_pair(key, true));
        }
    }

    int dfs(int node, int dicoverRank, vector<vector<int>>& connections, 
                            std::unordered_map<int, std::vector<int>>& graph, 
                                std::unordered_map<int, int>& rank, 
                                    std::unordered_map<std::pair<int, int>, bool, pair_hash>& connDict) {

        if (rank[node] != 0) {
            return rank[node];
        }

        rank[node] = dicoverRank;

        int minRank = dicoverRank + 1;

        for (int neighbor : graph[node]) {

            //skip the parent
            int neighorRank = rank[neighbor];
            if (neighorRank != 0 && neighorRank == dicoverRank - 1) {
                continue;
            }

            //recurse on the neighbor
            int recursiveRank = dfs(neighbor, dicoverRank + 1, connections, graph, rank, connDict);

            //step 1, check if this edge should be discarded
            if (recursiveRank <= dicoverRank) {

                int sortedU = std::min(node, neighbor);
                int sortedV = std::max(node, neighbor);
                connDict.erase({sortedU, sortedV});
            }

            //step 2, update the minRank if needed
            minRank = std::min(minRank, recursiveRank);

        }

        return minRank;
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        std::unordered_map<int, std::vector<int>> graph;
        std::unordered_map<int, int> rank;
        std::unordered_map<std::pair<int, int>, bool, pair_hash> connDict;

        editGraph(n, connections, graph, rank, connDict);

        dfs(0, 0, connections, graph, rank, connDict);

        std::vector<std::vector<int>> results;
        for (auto& criticalConn : connDict) {
            results.push_back({criticalConn.first.first, criticalConn.first.second});
        }

        return results;
    }
};
*/