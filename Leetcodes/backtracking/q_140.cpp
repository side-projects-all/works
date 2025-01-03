/*
Given a string s and a dictionary of strings wordDict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

 

Example 1:

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]

Example 2:

Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []

 

Constraints:

    1 <= s.length <= 20
    1 <= wordDict.length <= 1000
    1 <= wordDict[i].length <= 10
    s and wordDict[i] consist of only lowercase English letters.
    All the strings of wordDict are unique.
    Input is generated in a way that the length of the answer doesn't exceed 10^5.


*/

class Solution {
private:
    vector<string> backtracking(string& s, vector<string>& wordDict) {
        int N = s.size();
        std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());
        std::vector<std::string> ans;
        std::string curr;

        std::function<void(int)> bt = [&](int now) {
            if (now == N) {
                ans.push_back(curr);
                return;
            }

            for (int end = now + 1; end <= N; ++end) {
                std::string sub = s.substr(now, end - now);

                if (words.find(sub) != words.end()) {
                    std::string tmp = curr;
                    if (!curr.empty()) {
                        curr += " ";
                    }
                    curr += sub;
                    bt(end);

                    curr = tmp;
                }
            }
        };

        bt(0);

        return ans;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        return backtracking(s, wordDict);
    }
};