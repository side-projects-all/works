/*
Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.

Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.

In the American keyboard:

    the first row consists of the characters "qwertyuiop",
    the second row consists of the characters "asdfghjkl", and
    the third row consists of the characters "zxcvbnm".

 

Example 1:

Input: words = ["Hello","Alaska","Dad","Peace"]

Output: ["Alaska","Dad"]

Explanation:

Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.

Example 2:

Input: words = ["omk"]

Output: []

Example 3:

Input: words = ["adsdf","sfd"]

Output: ["adsdf","sfd"]

 

Constraints:

    1 <= words.length <= 20
    1 <= words[i].length <= 100
    words[i] consists of English letters (both lowercase and uppercase). 


*/

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        std::vector<std::string> ans;

        std::array<std::unordered_set<char>, 3> rows;
        rows[0] = { 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p' };
        rows[1] = { 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l' };
        rows[2] = { 'z', 'x', 'c', 'v', 'b', 'n', 'm' };

        for (int i = 0; i < words.size(); ++i) {

            char first = std::tolower(words[i][0]);
            int n = 0;
            for (int j = 0; j < rows.size(); ++j) {

                if (rows[j].find(first) != rows[j].end()) {
                    n = j;
                    break;
                }
            }

            bool same_row = true;
            for (int k = 1; k < words[i].size(); ++k) {

                char c = std::tolower(words[i][k]);
                if (rows[n].find(c) == rows[n].end()) {
                    same_row = false;
                    break;
                }
            }

            if (same_row) {
                ans.push_back(words[i]);
            }
        }

        return ans;
    }
};