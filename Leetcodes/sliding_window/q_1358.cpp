/*
Given a string s consisting only of characters a, b and c.

Return the number of substrings containing at least one occurrence of all these characters a, b and c.

 

Example 1:

Input: s = "abcabc"
Output: 10
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again). 

Example 2:

Input: s = "aaacb"
Output: 3
Explanation: The substrings containing at least one occurrence of the characters a, b and c are "aaacb", "aacb" and "acb". 

Example 3:

Input: s = "abc"
Output: 1

 

Constraints:

    3 <= s.length <= 5 x 10^4
    s only consists of a, b or c characters.


*/

class Solution {
private:
    int by_sliding_window(string& s) {
        int n = s.size();
        int b = 0;
        int e = 0;

        std::vector<int> freq(3);
        int cnt = 0;

        while (e < n) {
            char curr = s[e];
            ++freq[curr - 'a'];

            while (freq[0] > 0 && freq[1] > 0 && freq[2] > 0) {
                cnt += n - e;

                char begin_ch = s[b];
                --freq[begin_ch - 'a'];
                ++b;
            }

            ++e;
        }

        return cnt;
    }
    int by_last_position_tracking(string& s) {
        int n = s.size();
        std::vector<int> last_pos{-1, -1, -1};
        int total = 0;

        for (int i = 0; i < n; ++i) {
            last_pos[s[i] - 'a'] = i;

            total += 1 + std::min({last_pos[0], last_pos[1], last_pos[2]});
        }

        return total;
    }
public:
    int numberOfSubstrings(string s) {
        //return by_last_position_tracking(s);
        return by_sliding_window(s);
    }
};