/*
We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:

    "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

Given a string s, return the number of unique non-empty substrings of s are present in base.

 

Example 1:

Input: s = "a"
Output: 1
Explanation: Only the substring "a" of s is in base.

Example 2:

Input: s = "cac"
Output: 2
Explanation: There are two substrings ("a", "c") of s in base.

Example 3:

Input: s = "zab"
Output: 6
Explanation: There are six substrings ("z", "a", "b", "za", "ab", and "zab") of s in base.

 

Constraints:

    1 <= s.length <= 10^5
    s consists of lowercase English letters.


*/

class Solution {
private:
    int by_iterative_dp(std::string& s) {
        //using the characteristic of dp array storing all longest substring from every letter
        int n = s.size();
        if (n == 1) {
            return 1;
        }

        std::vector<int> dp_letter_longest_substr(26);
        int curr_len = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && (s[i] - s[i - 1] + 26) % 26 == 1) {
                ++curr_len;

            } else {
                curr_len = 1;
            }

            dp_letter_longest_substr[s[i] - 'a'] = std::max(dp_letter_longest_substr[s[i] - 'a'], curr_len);
        }

        int ans = 0;
        for (int i = 0; i < 26; ++i) {
            ans += dp_letter_longest_substr[i];
        }

        return ans;
    }
public:
    int findSubstringInWraproundString(string s) {
        return by_iterative_dp(s);
    }
};