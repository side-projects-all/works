/*
You are given two strings, s and t.

You can create a new string by selecting a

from s (possibly empty) and a substring from t (possibly empty), then concatenating them in order.

Return the length of the longest

that can be formed this way.

 

Example 1:

Input: s = "a", t = "a"

Output: 2

Explanation:

Concatenating "a" from s and "a" from t results in "aa", which is a palindrome of length 2.

Example 2:

Input: s = "abc", t = "def"

Output: 1

Explanation:

Since all characters are different, the longest palindrome is any single character, so the answer is 1.

Example 3:

Input: s = "b", t = "aaaa"

Output: 4

Explanation:

Selecting "aaaa" from t is the longest palindrome, so the answer is 4.

Example 4:

Input: s = "abcde", t = "ecdba"

Output: 5

Explanation:

Concatenating "abc" from s and "ba" from t results in "abcba", which is a palindrome of length 5.

 

Constraints:

    1 <= s.length, t.length <= 30
    s and t consist of lowercase English letters.

*/

class Solution {
private:
    bool is_palindrome(std::string& t, int b, int e) {
        while (b < e) {

            if (t[b] != t[e]) {
                return false;
            }

            ++b;
            --e;
        }
        return true;
    }
    int find_palindrome(std::string& s, int& sn, std::string& t, int& tn) {
        
        std::vector<std::string> subs_s;
        subs_s.push_back(s);
        for (int len = sn - 1; len >= 1; --len) {
            for (int b = 0; b <= sn - len; ++b) {
                subs_s.push_back(s.substr(b, len));
            }
        }
        subs_s.push_back("");

        std::vector<std::string> subs_t;
        subs_t.push_back(t);
        for (int len = tn - 1; len >= 1; --len) {
            for (int b = 0; b <= tn - len; ++b) {
                subs_t.push_back(t.substr(b, len));
            }
        }
        subs_t.push_back("");

        int longest = 1;
        for (int i = 0; i < subs_s.size(); ++i) {
            for (int j = 0; j < subs_t.size(); ++j) {
                std::string merge = subs_s[i] + subs_t[j];
                if (!merge.empty() && is_palindrome(merge, 0, merge.size() - 1)) {

                    longest = std::max(longest, (int)merge.size());
                }
            }
        }

        return longest;
    }
public:
    int longestPalindrome(std::string s, std::string t) {
        int sn = s.size();
        int tn = t.size();
        
        return find_palindrome(s, sn, t, tn);
    }
};
