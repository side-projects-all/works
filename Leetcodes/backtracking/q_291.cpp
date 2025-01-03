/*
Given a pattern and a string s, return true if s matches the pattern.

A string s matches a pattern if there is some bijective mapping of single characters to non-empty strings such that if each character in pattern is replaced by the string it maps to, then the resulting string is s. A bijective mapping means that no two characters map to the same string, and no character maps to two different strings.

 

Example 1:

Input: pattern = "abab", s = "redblueredblue"
Output: true
Explanation: One possible mapping is as follows:
'a' -> "red"
'b' -> "blue"

Example 2:

Input: pattern = "aaaa", s = "asdasdasdasd"
Output: true
Explanation: One possible mapping is as follows:
'a' -> "asd"

Example 3:

Input: pattern = "aabb", s = "xyzabcxzyabc"
Output: false

 

Constraints:

    1 <= pattern.length, s.length <= 20
    pattern and s consist of only lowercase English letters.


*/

class Solution {
private:
    bool backtracking(string& pattern, string& s) {
        int P = pattern.size();
        int S = s.size();
        std::unordered_map<char, std::string> symbols;
        std::unordered_set<std::string> words;

        std::function<bool(int, int)> bt = [&](int si, int pi) -> bool {
            if (pi == P) {
                return si == S;
            }

            char c = pattern[pi];

            if (symbols.find(c) != symbols.end()) {

                std::string word = symbols[c];
                if (s.compare(si, word.size(), word)) {
                    return false;
                }

                return bt(si + word.size(), pi + 1);
            }

            for (int now = si + 1; now <= S; ++now) {
                std::string new_word = s.substr(si, now - si);

                if (words.find(new_word) != words.end()) {
                    continue;
                }

                symbols[c] = new_word;
                words.insert(new_word);

                if (bt(now, pi + 1)) {
                    return true;
                }

                symbols.erase(c);
                words.erase(new_word);
            }

            return false;
        };

        return bt(0, 0);
    }

public:
    bool wordPatternMatch(string pattern, string s) {
        return backtracking(pattern, s);
    }
};