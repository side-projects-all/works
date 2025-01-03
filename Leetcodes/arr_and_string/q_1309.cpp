/*
You are given a string s formed by digits and '#'. We want to map s to English lowercase characters as follows:

    Characters ('a' to 'i') are represented by ('1' to '9') respectively.
    Characters ('j' to 'z') are represented by ('10#' to '26#') respectively.

Return the string formed after mapping.

The test cases are generated so that a unique mapping will always exist.

 

Example 1:

Input: s = "10#11#12"
Output: "jkab"
Explanation: "j" -> "10#" , "k" -> "11#" , "a" -> "1" , "b" -> "2".

Example 2:

Input: s = "1326#"
Output: "acz"

 

Constraints:

    1 <= s.length <= 1000
    s consists of digits and the '#' letter.
    s will be a valid string such that mapping is always possible.


*/

class Solution {
public:
    string freqAlphabets(string s) {
        std::string ans = "";

        for (int i = 0; i < s.size(); ++i) {

            if (i + 2 < s.size() && s[i + 2] == '#') {
                char ch = std::stoi(s.substr(i, 2)) - 1 + 'a';
                ans += ch;
                i += 2;
            } else {
                ans += (s[i] - 49) + 'a';
            }
        }

        return ans;
    }
};