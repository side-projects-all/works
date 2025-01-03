/*
Given a string s, remove duplicate letters so that every letter appears once and only once. You must make sure your result is
the smallest in lexicographical order
among all possible results.

 

Example 1:

Input: s = "bcabc"
Output: "abc"

Example 2:

Input: s = "cbacdcbc"
Output: "acdb"

 

Constraints:

    1 <= s.length <= 10^4
    s consists of lowercase English letters.

*/

class Solution {
private:
    std::string by_greedy_stack(string& s) {
        std::stack<char> stack;
        std::vector<int> mp(26);
        int vis[26] = { 0 };

        for(char ch : s) {
            mp[ch - 'a']++;
        }

        for(char ch : s) {
            
            --mp[ch - 'a'];
            if(vis[ch - 'a']) {
                continue;
            }
            
            while(!stack.empty() && stack.top() >= ch && mp[stack.top() - 'a']) {
                vis[stack.top() - 'a'] = false;
                stack.pop();
            }
            stack.push(ch);
            vis[ch - 'a'] = true;
        }

        string ans="";
        while(!stack.empty()) {
            ans += stack.top();
            stack.pop();
        }

        std::reverse(ans.begin(), ans.end());
        return ans;
    }
    std::string by_greedy_recursive(string s) {
        int cnt[26];
        int pos = 0;

        for (int i = 0; i < s.size(); ++i) {
            ++cnt[s[i] - 'a'];
        }

        std::string ans;
        for (int i = 0; i < s.size(); ++i) {
            
            if (s[i] < s[pos]) {
                pos = i;
            }

            --cnt[s[i] - 'a'];
            if (cnt[s[i] - 'a'] == 0) {
                break;
            }
        }

        if (s.empty()) {
            return "";

        } else {
            std::string sub = s.substr(pos + 1);
            std::string removed;

            for (auto c : sub) {
                if (c != s[pos]) {
                    removed.push_back(c);
                }
            }

            return s[pos] + by_greedy_recursive(removed);
        }
    }
public:
    string removeDuplicateLetters(string s) {
        //return by_greedy_recursive(s);
        return by_greedy_stack(s);
    }
};