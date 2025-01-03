/*
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

 

Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.

 

Constraints:

    1 <= s.length <= 10^5
    s consists of only uppercase English letters.
    0 <= k <= s.length


*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        int b = 0;
        std::vector<int> freq(26);
        int max_freq = 0;
        int longest = 0;

        for (int e = 0; e < s.size(); ++e) {
            int curr = s[e] - 'A';
            ++freq[curr];

            max_freq = std::max(max_freq, freq[curr]);

            bool is_valid = (e - b + 1 - max_freq <= k);    //e - b + 1 is window size!

            if (!is_valid) {
                int prev = s[b] - 'A';
                --freq[prev];

                ++b;
            }

            longest = e - b + 1;
        }

        return longest;
    }
};