/*
Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.

Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.

Note that you can return the indices of the edges in any order.

 

Example 1:

Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
Output: [[0,1],[2,3,4,5]]
Explanation: The figure above describes the graph.
The following figure shows all the possible MSTs:

Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.

Example 2:

Input: n = 4, edges = [[0,1,1],[1,2,1],[2,3,1],[0,3,1]]
Output: [[],[0,1,2,3]]
Explanation: We can observe that since all 4 edges have equal weight, choosing any 3 edges from the given 4 will yield an MST. Therefore all 4 edges are pseudo-critical.

 

Constraints:

    2 <= n <= 100
    1 <= edges.length <= min(200, n * (n - 1) / 2)
    edges[i].length == 3
    0 <= ai < bi < n
    1 <= weighti <= 1000
    All pairs (ai, bi) are distinct.


*/

class Solution {
private:
    class DSU {
    private:
        std::vector<int> root;
        std::vector<int> rank;

    public:
        int maxSize;

        DSU(int n) {
            root = std::vector<int>(n, 0);
            rank = std::vector<int>(n, 1);
            std::iota(root.begin(), root.end(), 0);
            maxSize = 1;
        }

        int find_root(int x) {
            if (x != root[x]) {
                return root[x] = find_root(root[x]);
            }

            return x;
        }

        bool union_set(int x, int y) {
            int rX = find_root(x);
            int rY = find_root(y);

            if (rX == rY) {
                return false;
            }

            /*
            if (rank[rX] < rank[rY]) {
                std::swap(rX, rY);
            }
            root[rY] = rX;
            rank[rX] += rank[rY];
            maxSize = max(maxSize, rank[rX]);
            */
            
            if (rank[rX] > rank[rY]) {
                root[rY] = rX;
                rank[rX] += rank[rY];

            } else if (rank[rX] < rank[rY]) {
                root[rX] = rY;
                rank[rY] += rank[rX];

            } else {
                root[rY] = rX;
                rank[rX] += rank[rY];
            }

            maxSize = std::max(maxSize, std::max(rank[rX], rank[rY]));
            
            return true;
        }
    };
    vector<vector<int>> byKruskal(int n, vector<vector<int>>& edges) {
  
        auto newEdges = edges;
        int N = newEdges.size();

        //for tracking
        for (int i = 0; i < N; ++i) {
            newEdges[i].push_back(i);
        }

        std::sort(newEdges.begin(), newEdges.end(), 
                        [&](const auto& v1, const auto& v2) {
                            return v1[2] < v2[2];
                        }
        );

        //calculate MST cost
        int minCost = 0;
        DSU dsu(n);
        for (int i = 0; i < newEdges.size(); ++i) {
            if (dsu.union_set(newEdges[i][0], newEdges[i][1])) {
                minCost += newEdges[i][2];
            }
        }

        //result[0]: all the critical, result[1]: pseudo-critical edges        
        std::vector<std::vector<int>> results(2);
        for (int i = 0; i < N; ++i) {
            DSU dsuIgnore(n);
            int ignoreCost = 0;

            //ignore current newEdges[i]
            for (int j = 0; j < N; ++j) {
                if (i != j && dsuIgnore.union_set(newEdges[j][0], newEdges[j][1])) {
                    ignoreCost += newEdges[j][2];
                }
            }

            if (dsuIgnore.maxSize < n || ignoreCost > minCost) {
                results[0].push_back(newEdges[i][3]);

            } else {
                DSU dsuAdd(n);

                //add current newEdges[i]
                dsuAdd.union_set(newEdges[i][0], newEdges[i][1]);
                int addWeight = newEdges[i][2];

                for (int j = 0; j < N; ++j) {
                    if (i != j && dsuAdd.union_set(newEdges[j][0], newEdges[j][1])) {
                        addWeight += newEdges[j][2];
                    }
                }

                if (addWeight == minCost) {
                     results[1].push_back(newEdges[i][3]);
                }
            }
        }

        return results;
    }
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        return byKruskal(n, edges);
    }
};