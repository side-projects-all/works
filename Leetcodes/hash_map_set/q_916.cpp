/*
You are given two string arrays words1 and words2.

A string b is a subset of string a if every letter in b occurs in a including multiplicity.

    For example, "wrr" is a subset of "warrior" but is not a subset of "world".

A string a from words1 is universal if for every string b in words2, b is a subset of a.

Return an array of all the universal strings in words1. You may return the answer in any order.

 

Example 1:

Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["e","o"]
Output: ["facebook","google","leetcode"]

Example 2:

Input: words1 = ["amazon","apple","facebook","google","leetcode"], words2 = ["l","e"]
Output: ["apple","google","leetcode"]

 

Constraints:

    1 <= words1.length, words2.length <= 10^4
    1 <= words1[i].length, words2[i].length <= 10
    words1[i] and words2[i] consist only of lowercase English letters.
    All the strings of words1 are unique.


*/

class Solution {
private:
    std::vector<int> counter(std::string& w) {
        std::vector<int> count(26);
        for (char c : w) {
            ++count[c - 'a'];
        }

        return count;
    }
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        std::vector<int> cnt(26);
        std::vector<int> tmp(26);

        for (std::string& w : words2) {
            tmp = counter(w);

            for (int i = 0; i < 26; ++i) {
                cnt[i] = std::max(cnt[i], tmp[i]);
            }
        }

        std::vector<std::string> ans;
        for (std::string& w : words1) {
            tmp = counter(w);

            bool has_all = true;
            for (int i = 0; i < 26; ++i) {
                if (tmp[i] < cnt[i]) {
                    has_all = false;
                    break;
                }
            }

            if (has_all) {
                ans.push_back(w);
            }
        }

        return ans;
    }
};