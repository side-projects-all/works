/*
You are given a string s that consists of lower case English letters and brackets.

Reverse the strings in each pair of matching parentheses, starting from the innermost one.

Your result should not contain any brackets.

 

Example 1:

Input: s = "(abcd)"
Output: "dcba"

Example 2:

Input: s = "(u(love)i)"
Output: "iloveu"
Explanation: The substring "love" is reversed first, then the whole string is reversed.

Example 3:

Input: s = "(ed(et(oc))el)"
Output: "leetcode"
Explanation: First, we reverse the substring "oc", then "etco", and finally, the whole string.

 

Constraints:

    1 <= s.length <= 2000
    s only contains lower case English characters and parentheses.
    It is guaranteed that all parentheses are balanced.


*/

class Solution {
private:
    std::string better_by_stack(std::string& s) {
        std::stack<int> stack;
        std::vector<int> pair(s.size());

        
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stack.push(i);

            }
            
            if (s[i] == ')') {
                int j = stack.top();
                stack.pop();

                pair[i] = j;
                pair[j] = i;
            }
        }

        std::string ans;
        for (int i = 0, dir = 1; i < s.size(); i += dir) {
            if (s[i] == '(' || s[i] == ')') {
                i = pair[i];
                dir = -dir;
            } else {
                ans += s[i];
            }
        }

        return ans;
    }
    std::string basic_by_stack(std::string& s) {
        std::stack<int> stack;

        std::string ans;
        for (int i = 0; i < s.size(); ++i) {

            if (s[i] == '(') {
                stack.push(ans.size());

            } else if (s[i] == ')') {
                int b = stack.top();
                stack.pop();

                std::reverse(ans.begin() + b, ans.end());
            } else {
                ans += s[i];
            }
        }

        return ans;
    }
public:
    string reverseParentheses(string s) {
        //return basic_by_stack(s);
        
        return better_by_stack(s);
    }
};