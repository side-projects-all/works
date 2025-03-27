/*
There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, and city b is connected directly with city c, then city a is connected indirectly with city c.

A province is a group of directly or indirectly connected cities and no other cities outside of the group.

You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

 

Example 1:

Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]
Output: 2

Example 2:

Input: isConnected = [[1,0,0],[0,1,0],[0,0,1]]
Output: 3

 

Constraints:

    1 <= n <= 200
    n == isConnected.length
    n == isConnected[i].length
    isConnected[i][j] is 1 or 0.
    isConnected[i][i] == 1
    isConnected[i][j] == isConnected[j][i]


*/

class Solution {
private:
    std::vector<int> rank;
    std::vector<int> parent;
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
            rank[rx] += rank[ry];   //using nodes number to represent the rank

        } else {
            parent[rx] = ry;
            rank[ry] += rank[rx]; 
        }
    }
    int by_union_find(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        if (n == 1) {
            return 1;
        }

        parent.resize(n + 1, -1);
        rank.resize(n + 1, 1);

        for (int r = 0; r < n; ++r) {
            for (int c = r + 1; c < n; ++c) {
                if (isConnected[r][c] == 1) {
                    union_set(r + 1, c + 1);
                }
            }
        }

        int cnt = 0;
        for (int i = 1; i <= n; ++i) {
            if (parent[i] == -1) {
                ++cnt;
            }
        }

        return cnt;
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        return by_union_find(isConnected);
    }
};