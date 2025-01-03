/*
Design a data structure that will be initialized with a string array, and then it should answer queries of the shortest distance between two different strings from the array.

Implement the WordDistance class:

    WordDistance(String[] wordsDict) initializes the object with the strings array wordsDict.
    int shortest(String word1, String word2) returns the shortest distance between word1 and word2 in the array wordsDict.

 

Example 1:

Input
["WordDistance", "shortest", "shortest"]
[[["practice", "makes", "perfect", "coding", "makes"]], ["coding", "practice"], ["makes", "coding"]]
Output
[null, 3, 1]

Explanation
WordDistance wordDistance = new WordDistance(["practice", "makes", "perfect", "coding", "makes"]);
wordDistance.shortest("coding", "practice"); // return 3
wordDistance.shortest("makes", "coding");    // return 1

 

Constraints:

    1 <= wordsDict.length <= 3 * 10^4
    1 <= wordsDict[i].length <= 10
    wordsDict[i] consists of lowercase English letters.
    word1 and word2 are in wordsDict.
    word1 != word2
    At most 5000 calls will be made to shortest.


*/

class WordDistance {
private:
    std::unordered_map<std::string, std::vector<int>> m;

public:
    WordDistance(vector<string>& wordsDict) {
        for (int i = 0; i < wordsDict.size(); ++i) {
            m[wordsDict[i]].push_back(i);
        }
    }
    
    int shortest(string word1, string word2) {
        int dis = INT_MAX;
        int i1 = 0;
        int i2 = 0;

        while (i1 < m[word1].size() && i2 < m[word2].size()) {
            dis = std::min(dis, std::abs(m[word1][i1] - m[word2][i2]));

            if (m[word1][i1] < m[word2][i2]) {
                ++i1;

            } else {
                ++i2;
            }
        }

        return dis;
    }
};

/**
 * Your WordDistance object will be instantiated and called as such:
 * WordDistance* obj = new WordDistance(wordsDict);
 * int param_1 = obj->shortest(word1,word2);
 */