/*
You are given a 2D integer array properties having dimensions n x m and an integer k.

Define a function intersect(a, b) that returns the number of distinct integers common to both arrays a and b.

Construct an undirected graph where each index i corresponds to properties[i]. There is an edge between node i and node j if and only if intersect(properties[i], properties[j]) >= k, where i and j are in the range [0, n - 1] and i != j.

Return the number of connected components in the resulting graph.

 

Example 1:

Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1

Output: 3

Explanation:

The graph formed has 3 connected components:

Example 2:

Input: properties = [[1,2,3],[2,3,4],[4,3,5]], k = 2

Output: 1

Explanation:

The graph formed has 1 connected component:

Example 3:

Input: properties = [[1,1],[1,1]], k = 2

Output: 2

Explanation:

intersect(properties[0], properties[1]) = 1, which is less than k. This means there is no edge between properties[0] and properties[1] in the graph.

 

Constraints:

    1 <= n == properties.length <= 100
    1 <= m == properties[i].length <= 100
    1 <= properties[i][j] <= 100
    1 <= k <= m


*/

class Solution {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int find(int x) {
        if (parent[x] == -1) {
            return x;
        }
        
        return parent[x] = find(parent[x]);
    }
    
    void union_set(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        
        if (rx == ry) {
            return;
        }
        
        if (rank[rx] > rank[ry]) {
            parent[ry] = rx;
            rank[rx] += rank[ry];
        } else {
            parent[rx] = ry;
            rank[ry] += rank[rx];
        }
    }
    
    bool intersect(int& k, std::vector<int>& v1, std::vector<int>& v2) {
        int cnt = 0;
        int cnt1[101]{ 0 };
        int cnt2[101]{ 0 };
        for (auto& v : v1) {
            ++cnt1[v];
        }

        for (auto& v : v2) {
            ++cnt2[v];
        }

        for (int i = 1; i <= 100; ++i) {
            if (cnt1[i] && cnt2[i]) {
                ++cnt;
            }
        }
        
        return cnt >= k;
    }
    
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int rows = properties.size();
        int cols = properties[0].size();
        parent.resize(rows, -1);
        rank.resize(rows, 1);
        
        for (int r = 0; r < rows; ++r) {
            for (int n = r + 1; n < rows; ++n) {
                if (intersect(k, properties[r], properties[n])) {
                    union_set(r, n);
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < rows; ++i) {
            if (parent[i] == -1) {
                ++ans;
            }
        }
        
        return ans;
    }
};