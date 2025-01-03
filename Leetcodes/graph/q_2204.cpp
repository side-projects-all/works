/*
You are given a positive integer n representing the number of nodes in a connected undirected graph containing exactly one cycle. The nodes are numbered from 0 to n - 1 (inclusive).

You are also given a 2D integer array edges, where edges[i] = [node1i, node2i] denotes that there is a bidirectional edge connecting node1i and node2i in the graph.

The distance between two nodes a and b is defined to be the minimum number of edges that are needed to go from a to b.

Return an integer array answer of size n, where answer[i] is the minimum distance between the ith node and any node in the cycle.

 

Example 1:

Input: n = 7, edges = [[1,2],[2,4],[4,3],[3,1],[0,1],[5,2],[6,5]]
Output: [1,0,0,0,0,1,2]
Explanation:
The nodes 1, 2, 3, and 4 form the cycle.
The distance from 0 to 1 is 1.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 3 is 0.
The distance from 4 to 4 is 0.
The distance from 5 to 2 is 1.
The distance from 6 to 2 is 2.

Example 2:

Input: n = 9, edges = [[0,1],[1,2],[0,2],[2,6],[6,7],[6,8],[0,3],[3,4],[3,5]]
Output: [0,0,0,1,2,2,1,2,2]
Explanation:
The nodes 0, 1, and 2 form the cycle.
The distance from 0 to 0 is 0.
The distance from 1 to 1 is 0.
The distance from 2 to 2 is 0.
The distance from 3 to 1 is 1.
The distance from 4 to 1 is 2.
The distance from 5 to 1 is 2.
The distance from 6 to 2 is 1.
The distance from 7 to 2 is 2.
The distance from 8 to 2 is 2.

 

Constraints:

    3 <= n <= 10^5
    edges.length == n
    edges[i].length == 2
    0 <= node1i, node2i <= n - 1
    node1i != node2i
    The graph is connected.
    The graph has exactly one cycle.
    There is at most one edge between any pair of vertices.


*/

class Solution {
public:
    vector<int> distanceToCycle(int n, vector<vector<int>>& edges) {
        vector<bool> isInCycle(n, true),
            visited(n, false);  // 'isInCycle' is initially true for all nodes
        vector<int> degree(n, 0), distances(n);
        vector<vector<int>> adjacencyList(n, vector<int>(0));

        // Build the adjacency list and calculate node degrees
        for (auto edge : edges) {
            adjacencyList[edge[0]].push_back(edge[1]);
            adjacencyList[edge[1]].push_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        queue<int> nodeQueue;

        // Start by adding all leaf nodes (degree 1) to the queue
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                nodeQueue.push(i);
            }
        }

        // Perform BFS to remove nodes with degree 1, progressively reducing the
        // graph
        while (!nodeQueue.empty()) {
            int currentNode = nodeQueue.front();
            nodeQueue.pop();
            isInCycle[currentNode] =
                false;  // Mark the node as not in the cycle

            // Update the degree of neighbors and add them to the queue if their
            // degree becomes 1
            for (auto neighbor : adjacencyList[currentNode]) {
                degree[neighbor]--;
                if (degree[neighbor] == 1) {
                    nodeQueue.push(neighbor);
                }
            }
        }

        // Add all cycle nodes to the queue and mark them as visited
        for (int currentNode = 0; currentNode < n; currentNode++) {
            if (isInCycle[currentNode]) {
                nodeQueue.push(currentNode);
                visited[currentNode] = true;
            }
        }

        // BFS to calculate distances from cycle nodes
        int currentDistance = 0;
        while (!nodeQueue.empty()) {
            int queueSize = nodeQueue.size();  // Track number of nodes to
                                               // process at this distance level
            for (int i = 0; i < queueSize; i++) {
                int currentNode = nodeQueue.front();
                nodeQueue.pop();

                distances[currentNode] =
                    currentDistance;  // Set the distance for the current node

                // Add unvisited neighbors to the queue
                for (auto neighbor : adjacencyList[currentNode]) {
                    if (visited[neighbor]) continue;
                    nodeQueue.push(neighbor);
                    visited[neighbor] = true;
                }
            }
            currentDistance++;  // Increment distance after processing all nodes
                                // at the current level
        }

        return distances;
    }
};
