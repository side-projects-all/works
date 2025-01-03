/*
You are given a string s and an array of strings words.

You should add a closed pair of bold tag <b> and </b> to wrap the substrings in s that exist in words.

    If two such substrings overlap, you should wrap them together with only one pair of closed bold-tag.
    If two substrings wrapped by bold tags are consecutive, you should combine them.

Return s after adding the bold tags.

 

Example 1:

Input: s = "abcxyz123", words = ["abc","123"]
Output: "<b>abc</b>xyz<b>123</b>"
Explanation: The two strings of words are substrings of s as following: "abcxyz123".
We add <b> before each substring and </b> after each substring.

Example 2:

Input: s = "aaabbb", words = ["aa","b"]
Output: "<b>aaabbb</b>"
Explanation: 
"aa" appears as a substring two times: "aaabbb" and "aaabbb".
"b" appears as a substring three times: "aaabbb", "aaabbb", and "aaabbb".
We add <b> before each substring and </b> after each substring: "<b>a<b>a</b>a</b><b>b</b><b>b</b><b>b</b>".
Since the first two <b>'s overlap, we merge them: "<b>aaa</b><b>b</b><b>b</b><b>b</b>".
Since now the four <b>'s are consecutive, we merge them: "<b>aaabbb</b>".

 

Constraints:

    1 <= s.length <= 1000
    0 <= words.length <= 100
    1 <= words[i].length <= 1000
    s and words[i] consist of English letters and digits.
    All the values of words are unique.

*/

class Solution {
public:
    string addBoldTag(string s, vector<string>& words) {
        int N = s.size();
        std::vector<bool> bolds(N);

        //the hardest part of this question is this search loop
        for (const auto& w : words) {
            
            int start = s.find(w);
            while (start != -1) {
                //mark all indices of this word as bold-needed
                for (int i = start; i < start + w.size(); ++i) {
                    bolds[i] = true;
                }

                start = s.find(w, start + 1);
            }
        }

        std::string result = "";
        for (int i = 0; i < N; ++i) {
            if (bolds[i] && (i == 0 || !bolds[i - 1])) {
                result += "<b>";
            }

            result += s[i];

            if (bolds[i] && (i == N - 1 || !bolds[i + 1])) {
                result += "</b>";
            }
        }

        return result;
    }
};