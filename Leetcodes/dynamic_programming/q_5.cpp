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
    std::string byDP(std::string& s) {
        int N = s.size();
        if (N == 1) {
            return s;
        }

        if (N == 2) {
            return (s[0] == s[1]) ? s : std::string(1, s[0]);
        }

        std::vector<std::vector<bool>> mem(N, std::vector<bool>(N));
        mem[N - 1][N - 1] = true;

        int li = 0;
        int ri = 0;
        for (int i = 0; i < N - 1; ++i) {
            
            mem[i][i] = true;
            if (s[i] == s[i + 1]) {
                mem[i][i + 1] = true;
                li = i;
                ri = i + 1;
            }
        }

        for (int len = 3; len <= N; ++len) {
            
            for (int start = 0, end = start + len - 1; end < N; ++start, ++end) {
                
                if (s[start] == s[end] && mem[start + 1][end - 1]) {
                    mem[start][end] = true;
                    li = start;
                    ri = end;
                }
            }
        }

        return s.substr(li, ri - li + 1);
    }

    void get_longest_palindrome(int& b, int& e, int i, int j, std::string& s) {
        int left = i;
        int right = j;

        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }

        if ((right - 1 - left - 1) > (e - b)) {
            e = right - 1;
            b = left + 1;
        }
    }
    std::string by_two_ptr(std::string& s) {
        int N = s.size();
        if (N == 1) {
            return s;
        }

        int b = 0;
        int e = 0;
        for (int i = 0; i < N; ++i) {

            get_longest_palindrome(b, e, i, i, s);      //odd center
            get_longest_palindrome(b, e, i, i + 1, s);  //even center
        }

        return s.substr(b, e - b + 1);
    }
public:
    string longestPalindrome(string s) {
        //return byDP(s);
        return by_two_ptr(s);
    }
};