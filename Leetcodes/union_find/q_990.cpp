/*
You are given an array of strings equations that represent relationships between variables where each string equations[i] is of length 4 and takes one of two different forms: "xi==yi" or "xi!=yi".Here, xi and yi are lowercase letters (not necessarily different) that represent one-letter variable names.

Return true if it is possible to assign integers to variable names so as to satisfy all the given equations, or false otherwise.

 

Example 1:

Input: equations = ["a==b","b!=a"]
Output: false
Explanation: If we assign say, a = 1 and b = 1, then the first equation is satisfied, but not the second.
There is no way to assign the variables to satisfy both equations.

Example 2:

Input: equations = ["b==a","a==b"]
Output: true
Explanation: We could assign a = 1 and b = 1 to satisfy both equations.

 

Constraints:

    1 <= equations.length <= 500
    equations[i].length == 4
    equations[i][0] is a lowercase letter.
    equations[i][1] is either '=' or '!'.
    equations[i][2] is '='.
    equations[i][3] is a lowercase letter.


*/

class Solution {
private:
    bool byDSU(vector<string>& equations) {
        constexpr int N = 26;
        std::vector<int> root(N);
        std::iota(root.begin(), root.end(), 0);
        std::vector<int> rank(N, 1);

        std::function<int(int)> union_find = [&](int x) {
            if (root[x] != x) {
                root[x] = union_find(root[x]);
            }

            return root[x];
        };

        std::function<void(int, int)> union_set = [&](int x, int y) {
 
            int rootX = union_find(x);
            int rootY = union_find(y);

            if (rootX == rootY) {
                return;
            }

            if (rank[rootX] > rank[rootY]) {
                root[rootY] = rootX;

            } else if (rank[rootX] < rank[rootY]) {
                root[rootX] = rootY;

            } else {
                rank[rootX] += 1;
                root[rootY] = rootX;
            }
        };

        for (std::string& e : equations) {
            if (e[1] == '=') {
                int x = e[0] - 'a';
                int y = e[3] - 'a';
                union_set(x, y);
            }
        }

        for (std::string& e : equations) {
            if (e[1] == '!') {
                int x = e[0] - 'a';
                int y = e[3] - 'a';
                if (union_find(x) == union_find(y)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool byDfs(vector<string>& equations) {
        constexpr int N = 26;
        std::vector<std::vector<int>> adj(N);
        std::vector<int> visited(N, -1);

        for (std::string& e : equations) {
            if (e[1] == '=') {
                int x = e[0] - 'a';
                int y = e[3] - 'a';

                adj[x].push_back(y);
                adj[y].push_back(x);
            }
        }

        std::function<void(int, int)> dfs = [&](int node, int v) {
            if (visited[node] == -1) {
                visited[node] = v;

                for (int n : adj[node]) {
                    dfs(n, v);
                }
            }
        };

        for (int i = 0; i < N; ++i) {
            dfs(i, i);
        }

        for (std::string& e : equations) {
            if (e[1] == '!') {
                int x = e[0] - 'a';
                int y = e[3] - 'a';

                if (visited[x] == visited[y]) {
                    return false;
                }
            }
        }

        return true;
    }
public:
    bool equationsPossible(vector<string>& equations) {
        

        //return byDfs(equations);
        return byDSU(equations);
    }
};