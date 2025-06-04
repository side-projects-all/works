/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return all the shortest transformation sequences from beginWord to endWord, or an empty list if no such sequence exists. Each sequence should be returned as a list of the words [beginWord, s1, s2, ..., sk].

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: [["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]
Explanation: There are 2 shortest transformation sequences:
"hit" -> "hot" -> "dot" -> "dog" -> "cog"
"hit" -> "hot" -> "lot" -> "log" -> "cog"

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: []
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

 

Constraints:

    1 <= beginWord.length <= 5
    endWord.length == beginWord.length
    1 <= wordList.length <= 500
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.
    The sum of all shortest transformation sequences does not exceed 10^5.


*/

class Solution {
private:
    void back_tracking(const std::string& word, const std::string& beginWord, 
                        std::unordered_map<std::string, std::vector<std::string>>& parents, 
                            std::vector<std::string>& path, std::vector<std::vector<std::string>>& ans) {

        if (word == beginWord) {
            std::vector<std::string> tmp = path;
            std::reverse(tmp.begin(), tmp.end());
            ans.push_back(tmp);

            return;
        }

        for (const std::string& p : parents[word]) {
            path.push_back(p);

            back_tracking(p, beginWord, parents, path, ans);
            
            path.pop_back();
        }
    }
    vector<vector<string>> by_bfs_and_back_tracking(string& beginWord, string& endWord, vector<string>& wordList) {

        std::unordered_set<std::string> word_set(wordList.begin(), wordList.end());
        std::vector<std::vector<std::string>> ans;

        if (word_set.find(endWord) == word_set.end()) {
            return ans;
        }

        std::unordered_map<std::string, std::vector<std::string>> parents;
        std::unordered_map<std::string, int> depth;
        std::queue<std::string> q;

        q.push(beginWord);
        depth[beginWord] = 0;
        int level = 0;
        bool found = false;     //for earlier break out of loop when reach end word 

        while (!q.empty() && !found) {
            
            int sz = q.size();
            ++level;
            std::unordered_set<std::string> visited_in_this_level;

            for (int i = 0; i < sz; ++i) {
                
                std::string word = q.front();
                q.pop();
                std::string original = word;

                for (int j = 0; j < word.size(); ++j) {
                    char old = word[j];

                    for (char c = 'a'; c <= 'z'; ++c) {
                        word[j] = c;

                        if (word == original) {
                            continue;
                        }

                        if (word_set.find(word) != word_set.end()) {

                            if (depth.find(word) == depth.end()) {
                                depth[word] = level;
                                q.push(word);
                                visited_in_this_level.insert(word);
                                parents[word].push_back(original);

                            } else if (depth[word] == level) {

                                parents[word].push_back(original);
                            }

                            if (word == endWord) {
                                found = true;
                            }
                        }
                    }

                    word[j] = old;
                }
            }

            for (const std::string& w : visited_in_this_level) {
                word_set.erase(w);
            }
        }

        if (found) {
            std::vector<std::string> path = { endWord };
            back_tracking(endWord, beginWord, parents, path, ans);
        }

        return ans;
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        return by_bfs_and_back_tracking(beginWord, endWord, wordList);
    }
};