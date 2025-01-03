/*
You are given a string s. You can convert s to a
palindrome
by adding characters in front of it.

Return the shortest palindrome you can find by performing this transformation.

 

Example 1:

Input: s = "aacecaaa"
Output: "aaacecaaa"

Example 2:

Input: s = "abcd"
Output: "dcbabcd"

 

Constraints:

    0 <= s.length <= 5 * 10^4
    s consists of lowercase English letters only.


*/

class Solution {
private:
    std::string by_kmp(string& s) {
        int n = s.size();
        std::string rev{ s };

        std::reverse(rev.begin(), rev.end());
        std::string s_new = s + "#" + rev;
        int n_new = s_new.size();
        std::vector<int> prefix_table(n_new, 0);

        for (int i = 1; i < n_new; ++i) {
            int prefix_len = prefix_table[i - 1];
            while (prefix_len > 0 && s_new[i] != s_new[prefix_len]) {
                prefix_len = prefix_table[prefix_len - 1];
            }

            if (s_new[i] == s_new[prefix_len]) {
                ++prefix_len;
            }

            prefix_table[i] = prefix_len;
        }

        return rev.substr(0, n - prefix_table[n_new - 1]) + s;
    }
    std::string by_two_ptr(string s) {
        int n = s.size();
        int i = 0;

        for (int j = n - 1; j >= 0; --j) {
            if (s[i] == s[j]) {
                ++i;
            }
        }

        if (i == n) {
            return s;
        }

        std::string rest = s.substr(i);
        std::reverse(rest.begin(), rest.end());

        return rest + by_two_ptr(s.substr(0, i)) + s.substr(i);
    }
public:
    string shortestPalindrome(string s) {
        if (s.size() < 2) {
            return s;
        }

        //return by_two_ptr(s);
        return by_kmp(s);
    }
};