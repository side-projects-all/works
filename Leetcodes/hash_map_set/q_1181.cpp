/*
Given a list of phrases, generate a list of Before and After puzzles.

A phrase is a string that consists of lowercase English letters and spaces only. No space appears in the start or the end of a phrase. There are no consecutive spaces in a phrase.

Before and After puzzles are phrases that are formed by merging two phrases where the last word of the first phrase is the same as the first word of the second phrase.

Return the Before and After puzzles that can be formed by every two phrases phrases[i] and phrases[j] where i != j. Note that the order of matching two phrases matters, we want to consider both orders.

You should return a list of distinct strings sorted lexicographically.

 

Example 1:

Input: phrases = ["writing code","code rocks"]
Output: ["writing code rocks"]

Example 2:

Input: phrases = ["mission statement",
                  "a quick bite to eat",
                  "a chip off the old block",
                  "chocolate bar",
                  "mission impossible",
                  "a man on a mission",
                  "block party",
                  "eat my words",
                  "bar of soap"]
Output: ["a chip off the old block party",
         "a man on a mission impossible",
         "a man on a mission statement",
         "a quick bite to eat my words",
         "chocolate bar of soap"]

Example 3:

Input: phrases = ["a","b","a"]
Output: ["a"]

 

Constraints:

    1 <= phrases.length <= 100
    1 <= phrases[i].length <= 100


*/

class Solution {
public:
    vector<string> beforeAndAfterPuzzles(vector<string>& phrases) {
        int n = phrases.size();
        std::vector<std::pair<std::string, std::string>> b_n_e(n);

        std::size_t i = 0;
        for (const std::string& str : phrases) {
            std::size_t last_sp = str.find_last_of(' ');    //last space
            std::string first = str.substr(0, str.find(' '));
            std::string last = last_sp == std::string::npos ? str : str.substr(last_sp + 1);
            b_n_e[i] = {first, last};
            ++i;
        }

        std::set<std::string> m;
        for (i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                if (i == j) continue;

                if (b_n_e[i].first == b_n_e[j].second) {
                    std::string combined = phrases[j] + phrases[i].substr(b_n_e[i].first.size());
                    m.emplace(combined);
                }
            }
        }

        std::vector<std::string> ans(m.size());
        i = 0;
        for (const auto& s : m) {
            ans[i] = s;
            ++i;
        }

        return ans;
    }
};