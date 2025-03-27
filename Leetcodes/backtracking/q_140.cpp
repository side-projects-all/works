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
    vector<string> by_iterative_dp(string& s, vector<string>& wordDict) {
        int n = s.size();
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());
        std::unordered_map<int, std::vector<std::string>> dp; // dp[i]: sentences starting from index i
        dp[n] = {""}; // Base case: empty string can be formed at the end

        for (int b = n - 1; b >= 0; --b) {

            std::vector<std::string> curr_sentences;
            for (int e = b + 1; e <= n; ++e) {

                std::string word = s.substr(b, e - b);
                if (dict.count(word)) {

                    for (const std::string& sentence : dp[e]) {

                        if (sentence.empty()) {
                            curr_sentences.push_back(word);

                        } else {
                            curr_sentences.push_back(word + (" ") + sentence);
                        }
                    }
                }
            }
            dp[b] = std::move(curr_sentences);
        }

        return dp[0];
    }
    void back_tracking(string& s, std::unordered_set<std::string>& set, 
                            std::vector<std::string>& ans, int b, std::string&& curr) {
        int n = s.size();
        if (b == n) {
            ans.push_back(curr);
        }

        for (int e = b + 1; e <= n; ++e) {
            std::string pre = s.substr(b, e - b);
            
            if (set.find(pre) != set.end()) {

                if (curr.empty()) {
                    back_tracking(s, set, ans, e, std::move(pre));
                } else {
                    back_tracking(s, set, ans, e, std::move(curr + " " + pre));
                }
            }
        }
    }
    vector<string> by_back_tracking(string& s, vector<string>& wordDict) {
        std::vector<std::string> ans;
        std::unordered_set<std::string> set{wordDict.begin(), wordDict.end()};

        back_tracking(s, set, ans, 0, "");
        return ans;
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        //return by_back_tracking(s, wordDict);
        
        return by_iterative_dp(s, wordDict);
    }
};