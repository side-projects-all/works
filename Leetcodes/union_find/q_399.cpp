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
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        for (int i = 0; i < equations.size(); ++i) {
            std::vector<std::string> equation = equations[i];
            std::string dividend = equation[0];
            std::string divisor = equation[1];
            double quotient = values[i];

            unionSet(dividend, divisor, quotient);
        }

        std::vector<double> results = std::vector<double>(queries.size(), 0);

        for (int j = 0; j < queries.size(); ++j) {
            std::vector<std::string> query = queries[j];
            std::string dividend = query[0];
            std::string divisor = query[1];

            if (gidWeight.find(dividend) == gidWeight.end() || 
                gidWeight.find(divisor) == gidWeight.end()) {

                results[j] = -1;
            } else {
                std::pair<std::string, double> dividendEntry = find(dividend);
                std::pair<std::string, double> divisorEntry = find(divisor);

                std::string dividendGid = dividendEntry.first;
                std::string divisorGid = divisorEntry.first;
                double dividendWeight = dividendEntry.second;
                double divisorWeight = divisorEntry.second;


                if (dividendGid != divisorGid) {
                    results[j] = -1;

                } else {
                    results[j] = dividendWeight / divisorWeight;
                }
            }
        }
        
        return results;
    }

private:
    std::unordered_map<std::string, std::pair<std::string, double>> gidWeight;

    std::pair<std::string, double> find(std::string nodeId) {
        if (gidWeight.find(nodeId) == gidWeight.end()) {
            gidWeight.insert(std::make_pair(nodeId, std::make_pair(nodeId, 1.0)));
        }

        std::pair<std::string, double> entry = gidWeight.find(nodeId)->second;
        if (entry.first != nodeId) {
            std::pair<std::string, double> newEntry = find(entry.first);
            gidWeight[nodeId] = std::make_pair(newEntry.first, entry.second * newEntry.second);
        }

        return gidWeight[nodeId];
    }

    void unionSet(std::string dividend, std::string divisor, double value) {
        std::pair<std::string, double> dividendEntry = find(dividend);
        std::pair<std::string, double> divisorEntry = find(divisor);

        std::string dividendGid = dividendEntry.first;
        std::string divisorGid = divisorEntry.first;
        double dividendWeight = dividendEntry.second;
        double divisorWeight = divisorEntry.second;

        if (dividendGid != divisorGid) {
            gidWeight[dividendGid] = std::make_pair(divisorGid, divisorWeight * value / dividendWeight);
        }
    }
};