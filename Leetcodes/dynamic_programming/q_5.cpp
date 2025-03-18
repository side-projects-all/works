/*
Given a string s, return the longest
palindromic
substring
in s.

 

Example 1:

Input: s = "babad"
Output: "bab"
Explanation: "aba" is also a valid answer.

Example 2:

Input: s = "cbbd"
Output: "bb"

 

Constraints:

    1 <= s.length <= 1000
    s consist of only digits and English letters.


*/

class Solution {
private:
    std::string by_Manachers_alg(std::string& s) {
        std::string s_prime = "#";
        for (char c : s) {
            s_prime += c;
            s_prime += "#";
        }

        int n = s_prime.size();
        vector<int> palindrome_radii(n, 0);
        int center = 0;
        int radius = 0;

        for (int i = 0; i < n; i++) {
            int mirror = 2 * center - i;

            if (i < radius) {
                palindrome_radii[i] = std::min(radius - i, palindrome_radii[mirror]);
            }

            while (i + 1 + palindrome_radii[i] < n &&
                   i - 1 - palindrome_radii[i] >= 0 &&
                   s_prime[i + 1 + palindrome_radii[i]] ==
                       s_prime[i - 1 - palindrome_radii[i]]) {
                palindrome_radii[i]++;
            }

            if (i + palindrome_radii[i] > radius) {
                center = i;
                radius = i + palindrome_radii[i];
            }
        }

        int max_length = 0;
        int center_index = 0;
        for (int i = 0; i < n; i++) {
            if (palindrome_radii[i] > max_length) {
                max_length = palindrome_radii[i];
                center_index = i;
            }
        }

        int start_index = (center_index - max_length) / 2;

        return s.substr(start_index, max_length);
    }
    void expand(int& b, int& e, int i, int j, std::string& s) {
        int left = i;
        int right = j;

        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }

        //from the idea: (right - 1) - (left - 1) > e - b
        if (right - left > e - b) {
            e = right - 1;
            b = left + 1;
        }
    }
    std::string by_two_ptr(string& s) {
        if (s.size() == 1) {
            return s;
        }

        int b = 0;
        int e = 0;

        for (int i = 0; i < s.size(); ++i) {
            expand(b, e, i, i, s);
            expand(b, e, i, i + 1, s);
        }

        return s.substr(b, e - b + 1);
    }
    std::string by_iterative_dp(string& s) {
        if (s.size() == 1) {
            return s;
        }

        int n = s.size();
        std::vector<std::vector<bool>> dp(n, std::vector<bool>(n));

        for (int i = 0; i < n; ++i) {
            dp[i][i] = true;
        }

        int start = 0;
        int end = 0;
        for (int i = 0; i < n - 1; ++i) {
            if (s[i] == s[i + 1]) {
                dp[i][i + 1] = true;
                start = i;
                end = i + 1;
            }
        }

        for (int len = 3; len <= n; ++len) {
            for (int b = 0, e = b + len - 1; e < n; ++b, ++e) {

                if (s[b] == s[e] && dp[b + 1][e - 1]) {
                    dp[b][e] = true;
                    start = b;
                    end = e;
                }
            }
        }

        return s.substr(start, end - start + 1);
    }
public:
    string longestPalindrome(string s) {
        //return by_iterative_dp(s);

        //return by_two_ptr(s);
        return by_Manachers_alg(s);
    }
};