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
    void back_tracking(std::vector<std::string>& ans, int left, int right, int& n, std::string& curr) {
        if (curr.size() == 2 * n) {
            ans.push_back(curr);
            return;
        }

        if (left < n) {
            curr += "(";
            back_tracking(ans, left + 1, right, n, curr);
            curr.pop_back();
        }

        if (left > right) {
            curr += ")";
            back_tracking(ans, left, right + 1, n, curr);
            curr.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        std::vector<std::string> ans;
        std::string curr;
        back_tracking(ans, 0, 0, n, curr);

        return ans;
    }
};