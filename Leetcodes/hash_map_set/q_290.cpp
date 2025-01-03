/*
Given a pattern and a string s, find if s follows the same pattern.

Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in s.

 

Example 1:

Input: pattern = "abba", s = "dog cat cat dog"
Output: true

Example 2:

Input: pattern = "abba", s = "dog cat cat fish"
Output: false

Example 3:

Input: pattern = "aaaa", s = "dog cat cat dog"
Output: false

 

Constraints:

    1 <= pattern.length <= 300
    pattern contains only lower-case English letters.
    1 <= s.length <= 3000
    s contains only lowercase English letters and spaces ' '.
    s does not contain any leading or trailing spaces.
    All the words in s are separated by a single space.


*/

class Solution {
public:
    bool wordPattern(string pattern, string s) {
        std::unordered_map<char, std::string> m1;
        std::unordered_map<std::string, char> m2;

        int word_begin = 0;
        int word_cnt = 0;
        int i;
        for (i = 0; i < pattern.size(); ++i) {

            if (word_begin >= s.size()) {
                break;
            }

            int e = word_begin;
            while (e < s.size() && s[e] != ' ') {
                ++e;
            }

            std::string w = s.substr(word_begin, e - word_begin);

            if (m1.find(pattern[i]) == m1.end()) {

                if (m2.find(w) == m2.end()) {
                    m1[pattern[i]] = w;
                    m2[w] = pattern[i];
                } else {
                    return false;
                }
                
            } else if (m2[w] != pattern[i]) {
                return false;
            }

            word_begin = e + 1;
            ++word_cnt;
        }

        return i == pattern.size() && word_begin >= s.size();
    }
};