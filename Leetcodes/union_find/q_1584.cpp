/*
You are given an array points representing integer coordinates of some points on a 2D-plane, where points[i] = [xi, yi].

The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between them: |xi - xj| + |yi - yj|, where |val| denotes the absolute value of val.

Return the minimum cost to make all points connected. All points are connected if there is exactly one simple path between any two points.

 

Example 1:

Input: points = [[0,0],[2,2],[3,10],[5,2],[7,0]]
Output: 20
Explanation: 

We can connect the points as shown above to get the minimum cost of 20.
Notice that there is a unique path between every pair of points.

Example 2:

Input: points = [[3,12],[-2,5],[-4,1]]
Output: 18

 

Constraints:

    1 <= points.length <= 1000
    -10^6 <= xi, yi <= 10^6
    All pairs (xi, yi) are distinct.


*/

class UnionFind {
public:
    UnionFind(int size) {
        group = std::vector<int>(size);
        rank = std::vector<int>(size);

        for (int i = 0; i < size; ++i) {
            group[i] = i;
        }
    }

    int find(int node) {
        if (group[node] != node) {
            group[node] = find(group[node]);
        }

        return group[node];
    }

    bool join(int n1, int n2) {
        int group1 = find(n1);
        int group2 = find(n2);

        //it means they already connected.
        if (group1 == group2) {
            return false;
        }

        if (rank[group1] > rank[group2]) {
            group[group2] = group1;
        } else if (rank[group1] < rank[group2]) {
            group[group1] = group2;
        } else {
            group[group1] = group2;
            rank[group2] += 1;
        }

        return true;
    }

private:
    std::vector<int> group;
    std::vector<int> rank;
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        
        //return byKruskal(points);
        return byPrim(points);
    }

private: 
    int byKruskal(vector<vector<int>>& points) {
        int n = points.size();
        std::vector<std::pair<int, std::pair<int, int>>> allEdges;

        //create the graph
        for (int curr = 0; curr < n; ++curr) {
            for (int another = curr + 1; another < n; ++another) {
                int weight = std::abs(points[curr][0] - points[another][0]) + 
                             std::abs(points[curr][1] - points[another][1]);

                allEdges.push_back({ weight, { curr, another } });
            }
        }

        std::sort(allEdges.begin(), allEdges.end());

        //using union-find to decide if cycle 
        UnionFind uf(n);
        int mstCost = 0;
        int edgesUsed = 0;

        for (int i = 0; i < allEdges.size() && edgesUsed < n - 1; ++i) {
            int n1 = allEdges[i].second.first;
            int n2 = allEdges[i].second.second;
            int weight = allEdges[i].first;

            if (uf.join(n1, n2)) {
                mstCost += weight;
                ++edgesUsed;
            }
        }

        return mstCost;
    }

    struct Edge {
        int p1;
        int p2;
        int cost;
    };

    struct my_comparator {
        bool operator() (const Edge& e1, const Edge& e2) const {
            return e1.cost > e2.cost;
        }
    };

    int byPrim(vector<vector<int>>& points) {

        int n = points.size();
        std::priority_queue<Edge, std::vector<Edge>, my_comparator> pq;

        std::vector<bool> visited(n);
        visited[0] = true;

        int cost = 0;
        //we start from point[0]
        std::vector<int>& e0 = points[0];
        for (int i = 0; i < n; ++i) {
            std::vector<int>& p = points[i];
            int cost = std::abs(e0[0] - p[0]) + std::abs(e0[1] - p[1]);

            pq.push({0, i, cost});
        }

        int cnt = n - 1;    //for counting n - 1 edges
        int total = 0;
        while (!pq.empty() && cnt > 0) {
            Edge e = pq.top();
            pq.pop();

            int p1 = e.p1;
            int p2 = e.p2;
            int cost = e.cost;

            if (!visited[p2]) {
                total += cost;
                visited[p2] = true;

                for (int i = 0; i < n; ++i) {
                    if (!visited[i]) {
                        int cost = std::abs(points[i][0] - points[p2][0]) + std::abs(points[i][1] - points[p2][1]);
                        pq.push({p2, i, cost});
                    }
                }

                --cnt;
            }
        }

        return total;
        /*
        int n = points.size();
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> heap;

        std::vector<bool> inMST(n);

        heap.push({0, 0});  //{weight, point[0]}, the second val means the point we are going to start with.
        int mstCost = 0;
        int edgesUsed = 0;

        while (edgesUsed < n) {
            std::pair<int, int> top = heap.top();
            heap.pop();

            int weight = top.first;
            int curr = top.second;

            if (inMST[curr]) {
                continue;
            }

            inMST[curr] = true;
            mstCost += weight;
            ++edgesUsed;

            for (int next = 0; next < n; ++next) {
                if (!inMST[next]) {
                    int nextWeight = std::abs(points[curr][0] - points[next][0]) + 
                                        std::abs(points[curr][1] - points[next][1]);

                    heap.push({nextWeight, next});
                }
            }

        }

        return mstCost;
        */

    }
};