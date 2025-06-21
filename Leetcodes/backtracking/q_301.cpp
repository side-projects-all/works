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
    void back_tracking(string s, std::vector<std::string>& ans, const std::string& parentheses, int left, int right) {
        int cnt = 0;    // cnt > 1: too many left, cnt < 1: too many, cnt == 0: balanced
        int n = s.size();
        while (right < n) {
            char ch = s[right];

            if (ch == parentheses[0]) {
                ++cnt;

            } else if (ch == parentheses[1]) {
                --cnt;
            }

            if (cnt < 0) {
                break;      //too many right
            }

            ++right;
        }

        if (cnt < 0) {
            while (left <= right) {

                char c = s[left];
                if (c != parentheses[1] || (left > 0 && s[left] == s[left - 1])) {
                    ++left;
                    continue;
                }

                s.erase(left, 1);
                back_tracking(s, ans, parentheses, left, right);
                s.insert(s.begin() + left, parentheses[1]);

                ++left;
            }

        } else if (cnt > 0) {
            std::reverse(s.begin(), s.end());   //because we want to do upper while loop like left is right
            back_tracking(s, ans, ")(", 0, 0);

        } else {
            ans.push_back((parentheses[0] == '(') ? s : std::string(s.rbegin(), s.rend()));
        }
    }
    vector<string> by_back_tracking(string& s) {
        std::vector<std::string> ans;

        back_tracking(s, ans, "()", 0, 0);
        return ans;
    }
public:
    vector<string> removeInvalidParentheses(string s) {
        return by_back_tracking(s);
    }
};