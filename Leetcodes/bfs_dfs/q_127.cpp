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
public:
    int extendQueue(std::unordered_map<std::string, int>& currentSteps, 
                    std::unordered_map<std::string, int>& oppositeSteps, 
                    std::queue<std::string>& currentQueue, 
                    std::unordered_set<std::string>& words) {
      
        for (int i = currentQueue.size(); i > 0; --i) {
            std::string word = currentQueue.front();
            int step = currentSteps[word];
            currentQueue.pop();

            // Try to transform each position in the word
            for (int j = 0; j < word.size(); ++j) {
                char originalChar = word[j];

                // Replace the current character with all possible characters
                for (char c = 'a'; c <= 'z'; ++c) {
                    word[j] = c;
                    // Continue if the transformed word is the same or not in the word set
                    if (!words.count(word) || currentSteps.count(word)) continue;
                    // If the transformed word is in the opposite steps, a connection is found
                    if (oppositeSteps.count(word)) return step + oppositeSteps[word];

                    // Otherwise, add the transformed word into the current steps and queue
                    currentSteps[word] = step + 1;
                    currentQueue.push(word);
                }

                // Change back to the original character before trying the next position
                word[j] = originalChar;
            }
        }
        return -1;
    }
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Initialize a set with the words for fast lookup
        std::unordered_set<std::string> words(wordList.begin(), wordList.end());
        // If the end word is not in the set, no transformation sequence exists
        if (!words.count(endWord)) return 0;

        // Two queues for the bidirectional BFS
        std::queue<std::string> queueBegin{{beginWord}};
        std::queue<std::string> queueEnd{{endWord}};

        // Mapping from word to its number of steps from the begin word or end word
        std::unordered_map<std::string, int> stepsFromBegin;
        std::unordered_map<std::string, int> stepsFromEnd;

        // Initial steps counts for beginWord and endWord
        stepsFromBegin[beginWord] = 1;
        stepsFromEnd[endWord] = 1;

        // Bidirectional BFS
        while (!queueBegin.empty() && !queueEnd.empty()) {
            // Choose the direction with the smaller frontier for extension
            int result = queueBegin.size() <= queueEnd.size()
                ? extendQueue(stepsFromBegin, stepsFromEnd, queueBegin, words)
                : extendQueue(stepsFromEnd, stepsFromBegin, queueEnd, words);

            if (result != -1) return result; // If paths meet, return the result
        }
        return 0; // If no path is found, return 0
    }
};

