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
    std::vector<int> root;

    int findRoot(int x) {
        //path compression
        if (x == root[x]) {
            return x;
        }

        return root[x] = findRoot(root[x]);
    }

    void unionByRank(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;
                
            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;

            } else {
                root[rootY] = rootX;
                rank[rootX] += 1;

            }
        }
    }

public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        rank = std::vector<int>(isConnected.size(), 1);
        root = std::vector<int>(isConnected.size(), 0);

        for (int i = 0; i < isConnected.size(); ++i) {
            root[i] = i;
        }

        int result = isConnected.size();
        for (int r = 0; r < isConnected.size(); ++r) {
            for (int c = 0; c < isConnected[r].size(); ++c) {
                if (r == c) {
                    continue;
                }

                if (isConnected[r][c] == 1 && findRoot(r) != findRoot(c)) {
                    --result;
                    unionByRank(r, c);
                }
            }
        }

        return result;
    }
};