/*
You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.

You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.

Return the answers to all queries. If a single answer cannot be determined, return -1.0.

Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.

 

Example 1:

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]

Example 2:

Input: equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
Output: [3.75000,0.40000,5.00000,0.20000]

Example 3:

Input: equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
Output: [0.50000,2.00000,-1.00000,-1.00000]

 

Constraints:

    1 <= equations.length <= 20
    equations[i].length == 2
    1 <= Ai.length, Bi.length <= 5
    values.length == equations.length
    0.0 < values[i] <= 20.0
    1 <= queries.length <= 20
    queries[i].length == 2
    1 <= Cj.length, Dj.length <= 5
    Ai, Bi, Cj, Dj consist of lower case English letters and digits.


*/

class Solution {
private:
    double dfs(std::unordered_map<std::string, std::vector<std::pair<std::string, double>>>& adj, std::string& curr, std::string& dest, double curr_val, std::unordered_set<std::string>& visited) {
        if (curr == dest) {
            return curr_val;
        }

        visited.insert(curr);
        for (auto& [nei, weight] : adj[curr]) {
            
            double val = -1;
            if (!visited.contains(nei)) {
                val = dfs(adj, nei, dest, curr_val * weight, visited);

                if (val != -1) {
                    return val;
                }
            }
        }

        return -1;
    }

    vector<double> by_dfs(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {

        std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adj;
        int i = 0;
        for (std::vector<std::string> &e : equations) {
            adj[e[0]].push_back({e[1], values[i]});
            adj[e[1]].push_back({e[0], (double)1 / values[i]});
            ++i;
        }

        std::vector<double> ans;
        for (auto &q : queries) {
            std::unordered_set<std::string> visited;
            if (adj.contains(q[0]) && adj.contains(q[1])) {
                ans.push_back(dfs(adj, q[0], q[1], 1, visited));

            } else {
                ans.push_back(-1);
            }
        }

        return ans;
    }
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        return by_dfs(equations, values, queries);
    }
};

/*
class Solution {
private:
    //like the parent array in union find
    std::unordered_map<std::string, std::pair<std::string, double>> groups;

    std::pair<std::string, double> find(const std::string& id) {
        if (groups.find(id) == groups.end()) {
            groups[id] = {id, 1.0};
        }

        std::string group_id = groups[id].first;
        if (group_id != id) {
            std::pair<std::string, double> parent = find(group_id);

            //update here!!
            groups[id] = { parent.first, parent.second * groups[id].second };
        }

        return groups[id];
    }

    void union_set(const std::string& x, const std::string& y, const double& val) {
        //dd: dividend
        //ds: divisor
        std::pair<std::string, double> dd_gp = find(x);
        std::pair<std::string, double> ds_gp = find(y);

        std::string dd = dd_gp.first;    //dividend
        std::string ds = ds_gp.first;    //divisor
        double dd_val = dd_gp.second;
        double ds_val = ds_gp.second;

        if (dd != ds) {
            //union into the same group here!!
            groups[dd] = { ds, ds_val * val / dd_val };
        }
    }
    
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        //build union union_set
        for (int i = 0; i < equations.size(); ++i) {
            union_set(equations[i][0], equations[i][1], values[i]);
        }

        //find ans[i] for queries[i]
        std::vector<double> ans(queries.size());
        for (int i = 0; i < queries.size(); ++i) {

            if (groups.find(queries[i][0]) == groups.end() || groups.find(queries[i][1]) == groups.end()) {
                ans[i] = -1;
                continue;
            }

            std::pair<std::string, double> dd_gp = find(queries[i][0]);
            std::pair<std::string, double> ds_gp = find(queries[i][1]);

            if (dd_gp.first != ds_gp.first) {
                ans[i] = -1;

            } else {
                ans[i] = dd_gp.second / ds_gp.second;
            }
        }

        return ans;
    }   
};
*/