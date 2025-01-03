/*
There are n houses in a village. We want to supply water for all the houses by building wells and laying pipes.

For each house i, we can either build a well inside it directly with cost wells[i - 1] (note the -1 due to 0-indexing), or pipe in water from another well to it. The costs to lay pipes between houses are given by the array pipes where each pipes[j] = [house1j, house2j, costj] represents the cost to connect house1j and house2j together using a pipe. Connections are bidirectional, and there could be multiple valid connections between the same two houses with different costs.

Return the minimum total cost to supply water to all houses.

 

Example 1:

Input: n = 3, wells = [1,2,2], pipes = [[1,2,1],[2,3,1]]
Output: 3
Explanation: The image shows the costs of connecting houses using pipes.
The best strategy is to build a well in the first house with cost 1 and connect the other houses to it with cost 2 so the total cost is 3.

Example 2:

Input: n = 2, wells = [1,1], pipes = [[1,2,1],[1,2,2]]
Output: 2
Explanation: We can supply water with cost two using one of the three options:
Option 1:
  - Build a well inside house 1 with cost 1.
  - Build a well inside house 2 with cost 1.
The total cost will be 2.
Option 2:
  - Build a well inside house 1 with cost 1.
  - Connect house 2 with house 1 with cost 1.
The total cost will be 2.
Option 3:
  - Build a well inside house 2 with cost 1.
  - Connect house 1 with house 2 with cost 1.
The total cost will be 2.
Note that we can connect houses 1 and 2 with cost 1 or with cost 2 but we will always choose the cheapest option. 

 

Constraints:

    2 <= n <= 10^4
    wells.length == n
    0 <= wells[i] <= 10^5
    1 <= pipes.length <= 10^4
    pipes[j].length == 3
    1 <= house1j, house2j <= n
    0 <= costj <= 10^5
    house1j != house2j


*/

class Solution {
private:
    int byPrim(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                                std::greater<std::pair<int, int>>> heap;

        std::vector<std::vector<std::pair<int, int>>> adjList = 
                                std::vector<std::vector<std::pair<int, int>>>(n + 1);

        for (int i = 0; i < wells.size(); ++i) {
            std::pair<int, int> virtualEdge = std::make_pair(wells[i], i + 1);
            adjList[0].push_back(virtualEdge);
            heap.push(virtualEdge);
        }

        for (int i = 0; i < pipes.size(); ++i) {
            int h1 = pipes[i][0];
            int h2 = pipes[i][1];
            int cost = pipes[i][2];

            adjList[h1].push_back(std::make_pair(cost, h2));
            adjList[h2].push_back(std::make_pair(cost, h1));
        }

        std::unordered_set<int> mstSet = std::unordered_set<int>();
        mstSet.insert(0);

        int totalCost = 0;
        while(mstSet.size() < n + 1) {
            std::pair<int, int> edge = heap.top();
            heap.pop();
            int cost = edge.first;
            int nextHouse = edge.second;

            if (mstSet.find(nextHouse) != mstSet.end()) {
                continue;
            }

            mstSet.insert(nextHouse);
            totalCost += cost;

            for (std::pair<int, int> neighborEdge : adjList[nextHouse]) {
                if (mstSet.find(neighborEdge.second) == mstSet.end()) {
                    heap.push(neighborEdge);
                }
            }
        }

        return totalCost;
    }

    struct my_cmpr {
        bool operator() (const std::vector<int>& v1, const std::vector<int>& v2) const {
            return v1[2] < v2[2];
        }
    };

    int find_root(int x, std::vector<int>& root) {
        if (x != root[x]) {
            return root[x] = find_root(root[x], root);
        }

        return x;
    }

    bool union_set(int x, int y, std::vector<int>& root, std::vector<int>& rank) {
        int rX = find_root(x, root);
        int rY = find_root(y, root);

        if (rX == rY) {
            return false;
        }

        if (rank[rX] > rank[rY]) {
            root[rY] = rX;
        } else if (rank[rX] < rank[rY]) {
            root[rX] = rY;
        } else {
            root[rY] = rX;
            rank[rX] += 1;
        }

        return true;
    }
    int byKruskal(int n, vector<int>& wells, vector<vector<int>>& pipes) {
        std::vector<int> root(n + 1, 0);
        std::iota(root.begin(), root.end(), 0);
        std::vector<int> rank(n + 1, 1);
        
        //add virtual nodes to represent the cost of those wells
        std::vector<std::vector<int>> edges(wells.size() + pipes.size());

        for (int i = 0; i < wells.size(); ++i) {
            edges[i] = {0, i + 1, wells[i]};
        }

        for (int i = 0; i < pipes.size(); ++i) {
            edges[i + wells.size()] = pipes[i];
        }

        std::sort(edges.begin(), edges.end(), my_cmpr());

        int total = 0;
        for (const auto& v : edges) {
            int h1 = v[0];
            int h2 = v[1];
            int cost = v[2];

            if (union_set(h1, h2, root, rank)) {
                total += cost;
            }
        }
        return total;
    }
public:
    int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {

        return byPrim(n, wells, pipes);
        //return byKruskal(n, wells, pipes);        
    }
};