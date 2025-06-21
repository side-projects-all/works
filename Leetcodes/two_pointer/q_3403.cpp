/*
You are given a string word, and an integer numFriends.

Alice is organizing a game for her numFriends friends. There are multiple rounds in the game, where in each round:

    word is split into numFriends non-empty strings, such that no previous round has had the exact same split.
    All the split words are put into a box.

Find the

string from the box after all the rounds are finished.

 

Example 1:

Input: word = "dbca", numFriends = 2

Output: "dbc"

Explanation: 

All possible splits are:

    "d" and "bca".
    "db" and "ca".
    "dbc" and "a".

Example 2:

Input: word = "gggg", numFriends = 4

Output: "g"

Explanation: 

The only possible split is: "g", "g", "g", and "g".

 

Constraints:

    1 <= word.length <= 5 * 10^3
    word consists only of lowercase English letters.
    1 <= numFriends <= word.length

*/

class Solution {
private:
    std::string last_sub(string& s) {
        int i = 0;  //first string pos
        int j = 1;  //second string pos
        int n = s.size();

        while (j < n) {
            int k = 0;
            //move forward if they had same letters, this is for the range to skip
            while (j + k < n && s[i + k] == s[j + k]) {     
                ++k;
            }

            if (j + k < n && s[i + k] < s[j + k]) {
                int old_i = i;
                i = j;  //update i to new position
                j = std::max(j + 1, old_i + k + 1); //find a new j to compare

            } else {
                j = j + k + 1;  //j skip those same letters
            }
        }

        return s.substr(i, n - i);
    }
    std::string by_two_ptr(string& word, int& numFriends) {
        if (numFriends == 1) {
            return word;
        }

        std::string last = last_sub(word);
        int n = word.size();
        int m = last.size();
        return last.substr(0, std::min(m, n - numFriends + 1));
    }
public:
    string answerString(string word, int numFriends) {
        return by_two_ptr(word, numFriends);
    }
};