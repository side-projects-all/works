/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

 

Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:

Input: n = 1
Output: ["()"]

 

Constraints:

    1 <= n <= 8


*/

class Solution {
private:
    void backtracking(int& n, std::vector<std::string>& ans, std::string& curr, int left, int right) {
        if (curr.size() == 2 * n) {
            ans.push_back(curr);
        }

        if (left < n) {
            curr.push_back('(');
            backtracking(n, ans, curr, left + 1, right);
            curr.pop_back();
        }

        if (left > right) {
            curr.push_back(')');
            backtracking(n, ans, curr, left, right + 1);
            curr.pop_back();
        }
    }
    vector<string> by_backtracking(int& n) {
        if (n == 1) {
            return {"()"};
        }

        std::vector<std::string> ans;
        std::string curr;
        backtracking(n, ans, curr, 0, 0);

        return ans;
    }
public:
    vector<string> generateParenthesis(int n) {
        return by_backtracking(n);
    }
};