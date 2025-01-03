/*
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"

Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

 

Constraints:

    1 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] consists of only lowercase English letters.


*/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }

        //horizontal
        /*
        std::string prefix = strs[0];
        for (int i = 0; i < strs.size(); ++i) {
            while (strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.size() - 1);

                if (prefix.empty()) {
                    return "";
                }
            }
        }

        return prefix;
        */

        //vertical
        for (int i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];

            for (int p = 1; p < strs.size(); ++p) {
                if (i == strs[p].size() || strs[p][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }

        return strs[0];
    }
};