/*
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

    Every adjacent pair of words differs by a single letter.
    Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
    sk == endWord

Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.

Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

 

Constraints:

    1 <= beginWord.length <= 10
    endWord.length == beginWord.length
    1 <= wordList.length <= 5000
    wordList[i].length == beginWord.length
    beginWord, endWord, and wordList[i] consist of lowercase English letters.
    beginWord != endWord
    All the words in wordList are unique.


*/

class Solution {
private:
    int by_two_direction_bfs(std::string& beginWord, std::string& endWord, std::vector<std::string>& wordList) {
        int n = beginWord.size();
        std::unordered_set<std::string> set(wordList.begin(), wordList.end());

        if (set.find(endWord) == set.end()) {
            return 0;
        }

        std::unordered_set<std::string> visited;
        std::unordered_set<std::string> from_begin;
        std::unordered_set<std::string> from_end;

        int steps = 1;
        from_begin.insert(beginWord);
        from_end.insert(endWord);

        while (!from_begin.empty() && !from_end.empty()) {

            //choose smaller for better time complexity
            if (from_begin.size() > from_end.size()) {
                std::swap(from_begin, from_end);
            }

            std::unordered_set<std::string> next_level;
            for (std::string word : from_begin) {

                for (int i = 0; i < n; ++i) {
                    char old = word[i];

                    for (char c = 'a'; c <= 'z'; ++c) {
                        word[i] = c;

                        if (from_end.find(word) != from_end.end()) {
                            return steps + 1;
                        }

                        if (set.find(word) != set.end() && visited.find(word) == visited.end()) {
                            next_level.insert(word);
                            visited.insert(word);
                        }
                    }

                    word[i] = old;
                }
            }

            ++steps;
            from_begin = std::move(next_level);
        }

        return 0;
    }
    int by_one_direction_bfs(std::string& beginWord, std::string& endWord, std::vector<std::string>& wordList) {
        std::unordered_set<std::string> set(wordList.begin(), wordList.end());
        if (set.find(endWord) == set.end()) {
            return 0;
        }

        std::queue<std::pair<std::string, int>> q;
        q.push({beginWord,  1});
        set.erase(beginWord);

        while (!q.empty()) {
            auto [word, steps] = q.front();
            q.pop();

            if (word == endWord) {
                return steps;
            }

            for (int i = 0; i < word.size(); ++i) {
                char ch = word[i];

                for (char c = 'a'; c <= 'z'; ++c) {
                    word[i] = c;

                    if (set.find(word) != set.end()) {
                        set.erase(word);
                        q.push({word, steps + 1});
                    }
                }
                word[i] = ch;
            }
        }

        return 0;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        //return by_one_direction_bfs(beginWord, endWord, wordList);
        return by_two_direction_bfs(beginWord, endWord, wordList);
    }
};

