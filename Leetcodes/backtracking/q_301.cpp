/*
Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]

Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]

Example 3:

Input: s = ")("
Output: [""]

 

Constraints:

    1 <= s.length <= 25
    s consists of lowercase English letters and parentheses '(' and ')'.
    There will be at most 20 parentheses in s.


*/

class Solution {
private:
    std::vector<std::string> ans;
    const std::vector<char> para{'(', ')'};
public:
    std::vector<std::string> removeInvalidParentheses(std::string s) {
        backtracking(s, 0, 0, para);
        return ans;
        
    }

    void backtracking(std::string s, int left, int right, const std::vector<char>& para){
        int n = s.size();
        int cnt = 0;
        
        while (right < n) {
            char ch= s[right];

            if (ch == para[0]) {
                ++cnt;
            } else if (ch == para[1]) {
                --cnt;
            }

            if (cnt < 0) {
                break;
            }

            ++right;
        }

        if (cnt < 0) {
            while (left <= right) {
                char ch = s[left];
                if (ch != para[1] || (left > 0 && s[left] == s[left - 1])) {
                    ++left;
                    continue;
                }
                
                s.erase(left, 1);
                backtracking(s, left, right, para);
                s.insert(s.begin() + left, para[1]);

                ++left;
            }

        } else if (cnt > 0) { 
            std::reverse(s.begin(),s.end());
            backtracking(s, 0, 0, {')', '('});

        } else {
            ans.push_back(para[0] == '('? s : string(s.rbegin(), s.rend()));
        }
    }
};