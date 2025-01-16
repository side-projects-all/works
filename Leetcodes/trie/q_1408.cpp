/*
Given an array of string words, return all strings in words that is a substring of another word. You can return the answer in any order.

A substring is a contiguous sequence of characters within a string

 

Example 1:

Input: words = ["mass","as","hero","superhero"]
Output: ["as","hero"]
Explanation: "as" is substring of "mass" and "hero" is substring of "superhero".
["hero","as"] is also a valid answer.

Example 2:

Input: words = ["leetcode","et","code"]
Output: ["et","code"]
Explanation: "et", "code" are substring of "leetcode".

Example 3:

Input: words = ["blue","green","bu"]
Output: []
Explanation: No string of words is substring of another string.

 

Constraints:

    1 <= words.length <= 100
    1 <= words[i].length <= 30
    words[i] contains only lowercase English letters.
    All the strings of words are unique.


*/

class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        std::sort(words.begin(), words.end(), [](auto& w1, auto& w2) {
            return w1.size() < w2.size();
        });

        std::vector<std::string> ans;
        for (int i = 0; i < words.size(); ++i) {

            int j = i + 1;
            while (j < words.size() && words[i].size() <= words[j].size() && words[j].find(words[i]) == std::string::npos) {
                ++j;
            }

            if (j < words.size()) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
};