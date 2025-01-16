/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false

 

Constraints:

    1 <= s.length <= 300
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 20
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.


*/

class Solution {
private:
    bool iterative(std::string& s, std::vector<std::string>& wordDict) {
        std::vector<bool> dp(s.size());

        for (int i = 0; i < s.size(); ++i) {
            for (std::string& w : wordDict) {
                if (i < w.size() - 1) {
                    continue;
                }

                if (i == w.size() - 1 || dp[i - w.size()]) {
                    if (s.substr(i - w.size() + 1, w.size()) == w) {
                        dp[i] = true;
                        break;
                    }
                }
            }
        }

        return dp[s.size() - 1];
    }

    bool recursive(std::string& s, std::vector<std::string>& wordDict, int len, std::vector<int>& mem) {
        if (len < 0) {
            return true;
        }

        if (mem[len] != -1) {
            return mem[len];
        }

        for (std::string& w : wordDict) {
            int w_len = w.size();

            if (len - w_len + 1 < 0) {
                continue;
            }

            if (s.substr(len - w_len + 1, w_len) == w && recursive(s, wordDict, len - w_len, mem)) {
                return mem[len] = 1;
            }
        }

        return mem[len] = 0;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //std::vector<int> mem(s.size(), -1);

        //return recursive(s, wordDict, s.size() - 1, mem);
        return iterative(s, wordDict);
    }
};