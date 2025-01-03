/*
Given an array of strings words, return true if it forms a valid word square.

A sequence of strings forms a valid word square if the kth row and column read the same string, where 0 <= k < max(numRows, numColumns).

 

Example 1:

Input: words = ["abcd","bnrt","crmy","dtye"]
Output: true
Explanation:
The 1st row and 1st column both read "abcd".
The 2nd row and 2nd column both read "bnrt".
The 3rd row and 3rd column both read "crmy".
The 4th row and 4th column both read "dtye".
Therefore, it is a valid word square.

Example 2:

Input: words = ["abcd","bnrt","crm","dt"]
Output: true
Explanation:
The 1st row and 1st column both read "abcd".
The 2nd row and 2nd column both read "bnrt".
The 3rd row and 3rd column both read "crm".
The 4th row and 4th column both read "dt".
Therefore, it is a valid word square.

Example 3:

Input: words = ["ball","area","read","lady"]
Output: false
Explanation:
The 3rd row reads "read" while the 3rd column reads "lead".
Therefore, it is NOT a valid word square.

 

Constraints:

    1 <= words.length <= 500
    1 <= words[i].length <= 500
    words[i] consists of only lowercase English letters.


*/

class Solution {
private:
    bool naive2(vector<string>& words) {

        for (int r = 0; r < words.size(); ++r) {
            for (int c = 0; c < words[r].size(); ++c) {
  
                //r >= words[c].size() means row number is larger than or equal to 
                //the size of row of the column number, 
                //then we could not access the words[c][r]

                //c >= words.size() means character position is larger than number of rows
                //is also the same idea
                if (c >= words.size() || r >= words[c].size() || words[r][c] != words[c][r]) {
                    return false;
                }
            }
        }

        return true;
    }
    bool naive(vector<string>& words) {
        for (int r = 0; r < words.size(); ++r) {
            int r_len = words[r].size();
            int c_len = 0;

            //calculate column length
            for (int i = 0; i < words.size(); ++i) {
                if (words[i].size() > r) {
                    c_len += 1;
                }
            }

            if (r_len != c_len) {
                return false;
            }

            for (int c = 0; c < r_len; ++c) {
                if (words[r][c] != words[c][r]) {
                    return false;
                }
            }
        }

        return true;
    }
public:
    bool validWordSquare(vector<string>& words) {

        return naive(words);
        //return naive2(words);
    }
};