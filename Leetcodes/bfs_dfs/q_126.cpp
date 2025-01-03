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
    std::unordered_map<std::string, int> word_steps;
    std::vector<std::vector<std::string>> ans;
    std::string begin;

    void backtracking(std::vector<std::string>& curr_shortest, std::string word_now) {
        if (word_now == begin) {
            std::reverse(curr_shortest.begin(), curr_shortest.end());
            ans.push_back(curr_shortest);
            std::reverse(curr_shortest.begin(), curr_shortest.end());
            return;
        }

        for (int i = 0; i < word_now.size(); ++i) {
            char old = word_now[i];
            int steps = word_steps[word_now];

            for (char c = 'a'; c <= 'z'; ++c) {
                word_now[i] = c;

                if (word_steps.count(word_now) && word_steps[word_now] + 1 == steps) {
                    curr_shortest.push_back(word_now);
                    backtracking(curr_shortest, word_now);   
                    curr_shortest.pop_back();
                }
            }

            word_now[i] = old;
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        std::unordered_set<std::string> words(wordList.begin(), wordList.end());
        std::queue<std::string> q({beginWord});
        word_steps[beginWord] = 1;
        words.erase(beginWord);
        begin = beginWord;

        while (!q.empty()) {
            std::string now = q.front();
            q.pop();

            if (now == endWord) {
                break;
            }

            for (int i = 0; i < now.size(); ++i) {
                char old = now[i];
                int steps = word_steps[now];

                for (char c = 'a'; c <= 'z'; ++c) {
                    now[i] = c;

                    if (words.find(now) != words.end()) {
                        word_steps[now] = steps + 1;
                        words.erase(now);   //erase visited!!
                        q.push(now);
                    }
                }

                now[i] = old;
            }
        }

        if (word_steps.count(endWord)) {
            std::vector<std::string> curr;
            curr.push_back(endWord);

            //doing backtracking to find all shortest path
            backtracking(curr, endWord);
        }

        return ans;
    }
};