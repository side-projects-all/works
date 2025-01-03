/*
Given two strings s and t of lengths m and n respectively, return the minimum window
substring
of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

 

Example 1:

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:

Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:

Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.

 

Constraints:

    m == s.length
    n == t.length
    1 <= m, n <= 10^5
    s and t consist of uppercase and lowercase English letters.

*/

class Solution {
private:
    std::string slidingWindow(string& s, string& t) {
        int s_len = s.size();
        int t_len = t.size();

        if (s_len == 0 || t_len == 0 || s_len < t_len) {
            return "";
        }

        std::unordered_map<char, int> t_cnt;
        for (char& c : t) {
            ++t_cnt[c];
        }

        int min_sub[3]{ -1, 0, 0 };     //length, b, e
        int b = 0;
        int e = 0;
        int uniques = 0;
        std::unordered_map<char, int> curr_cnt;

        while (e < s_len) {
            char c_now = s[e];
            ++curr_cnt[c_now];

            if (t_cnt.find(c_now) != t_cnt.end() && t_cnt[c_now] == curr_cnt[c_now]) {
                ++uniques;
            }

            //moving left bound of the window
            while (b <= e && uniques == t_cnt.size()) {
                char c_leftmost = s[b];
                
                if (min_sub[0] == -1 || min_sub[0] > e - b + 1) {
                    min_sub[0] = e - b + 1;
                    min_sub[1] = b;
                    min_sub[2] = e;
                }

                --curr_cnt[c_leftmost];
                if (t_cnt.find(c_leftmost) != t_cnt.end() && t_cnt[c_leftmost] > curr_cnt[c_leftmost]) {
                    --uniques;
                }

                ++b;
            }

            ++e;
        }


        return min_sub[0] == -1 ? "" : s.substr(min_sub[1], min_sub[0]);
    }
public:
    string minWindow(string s, string t) {
        return slidingWindow(s, t);
    }
};