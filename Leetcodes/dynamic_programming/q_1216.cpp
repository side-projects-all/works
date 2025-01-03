/*
Given a string s and an integer k, return true if s is a k-palindrome.

A string is k-palindrome if it can be transformed into a palindrome by removing at most k characters from it.

 

Example 1:

Input: s = "abcdeca", k = 2
Output: true
Explanation: Remove 'b' and 'e' characters.

Example 2:

Input: s = "abbababa", k = 1
Output: true

 

Constraints:

    1 <= s.length <= 1000
    s consists of only lowercase English letters.
    1 <= k <= s.length


*/

class Solution {
private:
    int recursive(std::string& s, int k, int b, int e, std::vector<std::vector<int>>& mem) {
        if (b == e) {
            return 0;
        }

        if (b == e - 1) {
            return s[b] != s[e];
        }

        if (mem[b][e] != -1) {
            return mem[b][e];
        }

        int val = 0;
        if (s[b] == s[e]) {
            val = recursive(s, k, b + 1, e - 1, mem);
        } else {
            val = 1 + std::min(recursive(s, k, b, e - 1, mem), recursive(s, k, b + 1, e, mem));
        }

        mem[b][e] = val;
        return val;
    }

public:
    bool isValidPalindrome(string s, int k) {
        int N = s.size();
        std::vector<std::vector<int>> mem(s.size(), std::vector<int>(s.size(), -1));
        int cnt = recursive(s, k, 0, N - 1, mem);

        return cnt <= k;
    }
};