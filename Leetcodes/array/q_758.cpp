/*
Given an array of keywords words and a string s, make all appearances of all keywords words[i] in s bold. Any letters between <b> and </b> tags become bold.

Return s after adding the bold tags. The returned string should use the least number of tags possible, and the tags should form a valid combination.

 

Example 1:

Input: words = ["ab","bc"], s = "aabcd"
Output: "a<b>abc</b>d"
Explanation: Note that returning "a<b>a<b>b</b>c</b>d" would use more tags, so it is incorrect.

Example 2:

Input: words = ["ab","cb"], s = "aabcd"
Output: "a<b>ab</b>cd"

 

Constraints:

    1 <= s.length <= 500
    0 <= words.length <= 50
    1 <= words[i].length <= 10
    s and words[i] consist of lowercase English letters.

*/

class Solution {
public:
    string boldWords(vector<string>& words, string s) {
        int N = s.size();
        std::vector<bool> bolds(N);

        for (const auto& w : words) {

            int start = s.find(w);
            while (start != -1) {

                for (int i = start; i < start + w.size(); ++i) {
                    bolds[i] = true;
                }

                start = s.find(w, start + 1);
            }
        }

        std::string result = "";
        for (int i = 0; i < N; ++i) {
            //position of front <b>
            if (bolds[i] && (i == 0 || !bolds[i - 1])) {
                result += "<b>";
            }

            result += s[i];
            //position of end </b>
            if (bolds[i] && (i == N - 1 || !bolds[i + 1])) {
                result += "</b>";
            }
        }

        return result;
    }
};