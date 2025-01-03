/*
Numbers can be regarded as the product of their factors.

    For example, 8 = 2 x 2 x 2 = 2 x 4.

Given an integer n, return all possible combinations of its factors. You may return the answer in any order.

Note that the factors should be in the range [2, n - 1].

 

Example 1:

Input: n = 1
Output: []

Example 2:

Input: n = 12
Output: [[2,6],[3,4],[2,2,3]]

Example 3:

Input: n = 37
Output: []

 

Constraints:

    1 <= n <= 10^7


*/

class Solution {
private:
    void backtracking(std::vector<std::vector<int>>& ans, std::vector<int>& factors) {

        if (factors.size() > 1) {
            ans.push_back(factors);
        }

        const int lastFactor = factors.back();
        factors.pop_back();

        for (int i = factors.empty() ? 2 : factors.back(); i <= lastFactor / i; ++i) {
            if (lastFactor % i == 0) {

                //because of this requirement "i <= lastFactor / i", we could guarantee factors in 
                //ascending order
                factors.push_back(i);
                factors.push_back(lastFactor / i);

                backtracking(ans, factors);

                factors.pop_back();
                factors.pop_back();
            }
        }

        factors.push_back(lastFactor);
    }

    vector<vector<int>> dfs(int n) {
        std::vector<std::vector<int>> ans;
        std::stack<std::vector<int>> stk;
        stk.push({n});

        while (!stk.empty()) {
            std::vector<int> factors = stk.top();
            stk.pop();

            const int lastFactor = factors.back();
            factors.pop_back();

            for (int i = factors.empty() ? 2 : factors.back(); i <= lastFactor / i; ++i) {
                if (lastFactor % i == 0) {
                    std::vector<int> new_factors = factors;
                    new_factors.push_back(i);
                    new_factors.push_back(lastFactor / i);
                    stk.push(new_factors);
                    ans.push_back(new_factors);
                }
            }
        }

        return ans;
    }
public:
    vector<vector<int>> getFactors(int n) {
        
        std::vector<std::vector<int>> ans;
        std::vector<int> factors { n };
        backtracking(ans, factors);

        return ans;

        //return dfs(n);
    }
};