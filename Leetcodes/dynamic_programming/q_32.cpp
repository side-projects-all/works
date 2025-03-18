/*
Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses
substring
.

 

Example 1:

Input: s = "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()".

Example 2:

Input: s = ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()".

Example 3:

Input: s = ""
Output: 0

 

Constraints:

    0 <= s.length <= 3 * 10^4
    s[i] is '(', or ')'.


*/

class Solution {
private:
    int by_stack(string& s) {
        int n = s.size();
        if (n < 2) {
            return 0;
        }

        int max_len = 0;
        std::stack<int> stack;
        stack.push(-1);
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                stack.push(i);

            } else {
                stack.pop();
                if (stack.empty()) {
                    stack.push(i);

                } else {
                    max_len = std::max(max_len, i - stack.top());
                }
            }
        }

        return max_len;
    }
    int by_iterative_dp(string& s) {
        int n = s.size();
        if (n < 2) {
            return 0;
        }

        std::vector<int> dp(n); //LVP at index i
        int max_len = 0;
        for (int i = 1; i < n; ++i) {
            if (s[i] == ')') {  // ')' at index i

                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;

                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + (i - dp[i - 1] >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }

                max_len = std::max(max_len, dp[i]);
            }
        }

        return max_len;
    }
public:
    int longestValidParentheses(string s) {
        //return by_iterative_dp(s);
        
        return by_stack(s);
    }
};