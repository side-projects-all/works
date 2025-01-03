/*
Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.

 

Example 1:

Input: words = ["bella","label","roller"]
Output: ["e","l","l"]

Example 2:

Input: words = ["cool","lock","cook"]
Output: ["c","o"]

 

Constraints:

    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] consists of lowercase English letters.


*/

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        int N = words.size();
        std::vector<int> cnt(26, 0);
        std::vector<int> curr(26, 0);
        for (char c : words[0]) {
            ++cnt[c - 'a'];        
        }

        std::vector<std::string> ans;
        for (int i = 1; i < N; ++i) {
            std::fill(curr.begin(), curr.end(), 0);

            for (char c : words[i]) {
                ++curr[c - 'a'];
            }

            for (int letter = 0; letter < 26; ++letter) {
                cnt[letter] = std::min(cnt[letter], curr[letter]);
            }
        }

        for (int letter = 0; letter < 26; ++letter) {
            for (int commonCnt = 0; commonCnt < cnt[letter]; ++commonCnt) {
                ans.push_back(std::string(1, letter + 'a'));
            }
        }

        return ans;
    }
};