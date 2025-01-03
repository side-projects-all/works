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
public:
    vector<string> generateParenthesis(int n) {
        std::vector<std::string> result;

        backtracking(result, "", 0, 0, n);

        return result;
    }

private:

    void backtracking(std::vector<std::string>& result, std::string currStr, 
                        int leftCnt, int rightCnt, int n) {
        
        if (currStr.size() == 2 * n) {
            result.push_back(currStr);
            return;
        }

        if (leftCnt < n) {
            currStr += "(";
            backtracking(result, currStr, leftCnt + 1, rightCnt, n);
            currStr.erase(currStr.size() - 1, 1);
        }

        if (leftCnt > rightCnt) {
            currStr += ")";
            backtracking(result, currStr, leftCnt, rightCnt + 1, n);
            currStr.erase(currStr.size() - 1, 1);
        }

    }
};