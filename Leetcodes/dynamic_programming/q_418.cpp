/*
Given a rows x cols screen and a sentence represented as a list of strings, return the number of times the given sentence can be fitted on the screen.

The order of words in the sentence must remain unchanged, and a word cannot be split into two lines. A single space must separate two consecutive words in a line.

 

Example 1:

Input: sentence = ["hello","world"], rows = 2, cols = 8
Output: 1
Explanation:
hello---
world---
The character '-' signifies an empty space on the screen.

Example 2:

Input: sentence = ["a", "bcd", "e"], rows = 3, cols = 6
Output: 2
Explanation:
a-bcd- 
e-a---
bcd-e-
The character '-' signifies an empty space on the screen.

Example 3:

Input: sentence = ["i","had","apple","pie"], rows = 4, cols = 5
Output: 1
Explanation:
i-had
apple
pie-i
had--
The character '-' signifies an empty space on the screen.

 

Constraints:

    1 <= sentence.length <= 100
    1 <= sentence[i].length <= 10
    sentence[i] consists of lowercase English letters.
    1 <= rows, cols <= 2 * 10^4


*/

class Solution {
public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int n = sentence.size();
        int pos = 0;
        int ans = 0;

        std::vector<std::pair<int, int>> dp(n, {-1, -1});

        for (int i = 0; i < rows; ++i) {
            auto [next, cnt] = used_str(sentence, pos, cols, dp);

            pos = next;
            ans += cnt;
        }

        return ans;
    }
private:
    std::pair<int, int> used_str(std::vector<std::string>& sentence, int pos, int cols, std::vector<std::pair<int, int>>& dp) {
        if (dp[pos].first != -1) {
            return dp[pos];
        }

        int i = pos;
        int cnt = 0;
        int c = 0;

        while (c + sentence[i].size() <= cols) {
            c += sentence[i].size() + 1;

            if (++i == sentence.size()) {
                i = 0;
                ++cnt;
            }
        }

        return dp[pos] = {i, cnt};
    }
};