/*
Given an array of distinct strings words, return the minimal possible abbreviations for every word.

The following are the rules for a string abbreviation:

    The initial abbreviation for each word is: the first character, then the number of characters in between, followed by the last character.
    If more than one word shares the same abbreviation, then perform the following operation:
        Increase the prefix (characters in the first part) of each of their abbreviations by 1.
            For example, say you start with the words ["abcdef","abndef"] both initially abbreviated as "a4f". Then, a sequence of operations would be ["a4f","a4f"] -> ["ab3f","ab3f"] -> ["abc2f","abn2f"].
        This operation is repeated until every abbreviation is unique.
    At the end, if an abbreviation did not make a word shorter, then keep it as the original word.

 

Example 1:

Input: words = ["like","god","internal","me","internet","interval","intension","face","intrusion"]
Output: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]

Example 2:

Input: words = ["aa","aaa"]
Output: ["aa","aaa"]

 

Constraints:

    1 <= words.length <= 400
    2 <= words[i].length <= 400
    words[i] consists of lowercase English letters.
    All the strings of words are unique.


*/

class Solution {
private:
    int longest_common_prefix(const std::string& s1, const std::string& s2) {
        //if s1 and s2 have the same abbreviation, they definitely have the same length
        int i = 0;
        for (; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                return i;
            }
        }

        return i;
    }
    std::string abbreviate(const std::string& s) {
        if (s.size() <= 3) return s;

        return s[0] + std::to_string(s.size() - 2) + s.back();
    }

    vector<string> by_greedy_map(vector<string>& words) {
        int n = words.size();

        std::vector<std::string> ans(n);
        std::unordered_map<std::string, std::vector<int>> abbr; //for the same abbreviation to index vector
        for (int i = 0; i < n; ++i) {
            std::string after = abbreviate(words[i]);
            abbr[after].push_back(i);
            ans[i] = after;
        }

        for (auto& p : abbr) {
            if (p.second.size() < 2) continue;  //unique, no need to process

            auto& indices = p.second;
            int len = indices.size();
            std::vector<int> LCP(len);
            //loop through every combination of indcies to check if their need to be recovered or
            //do LCP abbreviation
            for (int i = 0; i < len; ++i) {
                std::string& curr = words[indices[i]];

                for (int j = i + 1; j < len; ++j) {
                    int prefix_len = longest_common_prefix(words[indices[i]], words[indices[j]]);

                    if (prefix_len > LCP[i]) LCP[i] = prefix_len;
                    if (prefix_len > LCP[j]) LCP[j] = prefix_len;
                }

                if (LCP[i] > curr.size() - 3) {
                    ans[indices[i]] = curr;   //recover to original word

                } else {
                    std::string rest = curr.substr(LCP[i]);
                    ans[indices[i]] = curr.substr(0, LCP[i]) + abbreviate(rest);
                }
            }
        }

        return ans;
    }
public:
    vector<string> wordsAbbreviation(vector<string>& words) {
        return by_greedy_map(words);
    }
};