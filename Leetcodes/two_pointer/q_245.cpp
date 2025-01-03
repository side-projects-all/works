/*

Given an array of strings wordsDict and two strings that already exist in the array word1 and word2, return the shortest distance between the occurrence of these two words in the list.

Note that word1 and word2 may be the same. It is guaranteed that they represent two individual words in the list.

 

Example 1:

Input: wordsDict = ["practice", "makes", "perfect", "coding", "makes"], word1 = "makes", word2 = "coding"
Output: 1

Example 2:

Input: wordsDict = ["practice", "makes", "perfect", "coding", "makes"], word1 = "makes", word2 = "makes"
Output: 3

 

Constraints:

    1 <= wordsDict.length <= 10^5
    1 <= wordsDict[i].length <= 10
    wordsDict[i] consists of lowercase English letters.
    word1 and word2 are in wordsDict.


*/

class Solution {
private:
    int by_two_ptr(vector<string>& wordsDict, string word1, string word2) {
        int prev = -1;
        int dis = INT_MAX;

        for (int i = 0; i < wordsDict.size(); ++i) {
            if (wordsDict[i] == word1 || wordsDict[i] == word2) {

                if (prev != -1 && (wordsDict[prev] != wordsDict[i] || word1 == word2)) {
                    dis = std::min(dis, i - prev);
                }

                prev = i;
            }
        }

        return dis;
    }
    int by_separate_case(vector<string>& wordsDict, string word1, string word2) {
        int w1 = -1;
        int w2 = -1;
        int dis = INT_MAX;

        if (word1 != word2) {
            for (int i = 0; i < wordsDict.size(); ++i) {

                if (wordsDict[i] == word1) {
                    w1 = i;
                }

                if (wordsDict[i] == word2) {
                    w2 = i;
                }

                if (w1 != -1 && w2 != -1) {
                    dis = std::min(dis, std::abs(w1 - w2));
                }
            }
        } else {
            std::vector<int> pos;
            for (int i = 0; i < wordsDict.size(); ++i) {
                if (wordsDict[i] == word1) {
                    pos.push_back(i);
                }
            }

            for (int i = 1; i < pos.size(); ++i) {
                dis = std::min(dis, std::abs(pos[i] - pos[i - 1]));
            }
        }
        
        return dis;
    }
public:
    int shortestWordDistance(vector<string>& wordsDict, string word1, string word2) {
        
       //return by_separate_case(wordsDict, word1, word2);
       return by_two_ptr(wordsDict, word1, word2);
    }
};