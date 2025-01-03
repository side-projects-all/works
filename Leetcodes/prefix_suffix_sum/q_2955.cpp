/*
You are given a 0-indexed string s, and a 2D array of integers queries, where queries[i] = [li, ri] indicates a substring of s starting from the index li and ending at the index ri (both inclusive), i.e. s[li..ri].

Return an array ans where ans[i] is the number of same-end substrings of queries[i].

A 0-indexed string t of length n is called same-end if it has the same character at both of its ends, i.e., t[0] == t[n - 1].

A substring is a contiguous non-empty sequence of characters within a string.

 

Example 1:

Input: s = "abcaab", queries = [[0,0],[1,4],[2,5],[0,5]]
Output: [1,5,5,10]
Explanation: Here is the same-end substrings of each query:
1st query: s[0..0] is "a" which has 1 same-end substring: "a".
2nd query: s[1..4] is "bcaa" which has 5 same-end substrings: "bcaa", "bcaa", "bcaa", "bcaa", "bcaa".
3rd query: s[2..5] is "caab" which has 5 same-end substrings: "caab", "caab", "caab", "caab", "caab".
4th query: s[0..5] is "abcaab" which has 10 same-end substrings: "abcaab", "abcaab", "abcaab", "abcaab", "abcaab", "abcaab", "abcaab", "abcaab", "abcaab", "abcaab".

Example 2:

Input: s = "abcd", queries = [[0,3]]
Output: [4]
Explanation: The only query is s[0..3] which is "abcd". It has 4 same-end substrings: "abcd", "abcd", "abcd", "abcd".

 

Constraints:

    2 <= s.length <= 3 * 10^4
    s consists only of lowercase English letters.
    1 <= queries.length <= 3 * 10^4
    queries[i] = [li, ri]
    0 <= li <= ri < s.length


*/


class Solution {
public:
    vector<int> sameEndSubstringCount(string s, vector<vector<int>>& queries) {
        int n = s.size();
        //for storing prefix sum of character frequencies for each character 'a' to 'z'
        std::vector<std::vector<int>> freq_prefix_sum(26, std::vector<int>(n, 0));

        //first count the frequency array
        for (int i = 0; i < n; i++) {
            freq_prefix_sum[s[i] - 'a'][i]++;
        }

        //turn the frequency array into a prefix sum array
        for (int i = 0; i < 26; i++) {
            for (int j = 1; j < n; j++) {
                freq_prefix_sum[i][j] += freq_prefix_sum[i][j - 1];
            }
        }

        std::vector<int> ans(queries.size());

        //loop each query
        for (int i = 0; i < queries.size(); i++) {
            int left = queries[i][0];
            int right = queries[i][1];
            int same_end_cnt = 0;

            //for each character, calculate the freq within the query range
            for (int c = 0; c < 26; ++c) {

                int left_freq = (left == 0) ? 0 : freq_prefix_sum[c][left - 1];
                int right_freq = freq_prefix_sum[c][right];
                int freq_in_range = right_freq - left_freq;

                same_end_cnt += freq_in_range * (freq_in_range + 1) / 2;
            }

            ans[i] = same_end_cnt;
        }

        return ans;
    }
};