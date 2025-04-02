/*
A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).

Given two strings source and target, return the minimum number of subsequences of source such that their concatenation equals target. If the task is impossible, return -1.

 

Example 1:

Input: source = "abc", target = "abcbc"
Output: 2
Explanation: The target "abcbc" can be formed by "abc" and "bc", which are subsequences of source "abc".

Example 2:

Input: source = "abc", target = "acdbc"
Output: -1
Explanation: The target string cannot be constructed from the subsequences of source string due to the character "d" in target string.

Example 3:

Input: source = "xyz", target = "xzyxz"
Output: 3
Explanation: The target string can be constructed as follows "xz" + "y" + "xz".

 

Constraints:

    1 <= source.length, target.length <= 1000
    source and target consist of lowercase English letters.


*/

class Solution {
private:
    int by_binary_search(string& source, string& target) {
        int sn = source.size();
        int tn = target.size();

        //sorted indices for every char
        std::vector<std::vector<int>> chars_indices(26, std::vector<int>());
        for (int i = 0; i < sn; ++i) {
            chars_indices[source[i] - 'a'].push_back(i);
        }

        int source_pos = 0;
        int cnt = 1;

        for (int i = 0; i < tn; ++i) {

            std::vector<int>& ch_ies = chars_indices[target[i] - 'a'];
            if (ch_ies.empty()) {
                return -1;
            }

            int ch_pos = std::lower_bound(ch_ies.begin(), 
                            ch_ies.end(), source_pos) - ch_ies.begin();
            
            //equal to the length of index vector for this characer, it means we can't have the same char anymore
            if (ch_pos == ch_ies.size()) {
                ++cnt;  //cut at the i of target
                source_pos = ch_ies[0] + 1;

            } else {
                source_pos = ch_ies[ch_pos] + 1;
            }
        }

        return cnt;
    }
    int by_two_ptr(string& source, string& target) {
        int sn = source.size();
        int tn = target.size();

        //preprocessing for counting
        std::vector<int> freq(26);
        for (int i = 0; i < sn; ++i) {
            ++freq[source[i] - 'a'];
        }

        for (int i = 0; i < tn; ++i) {
            if (freq[target[i] - 'a'] == 0) {
                return -1;
            }
        }

        int ans = 0;
        for (int i = 0; i < tn; ++i) {
            
            int tb = i;
            int sb = 0;
            int cnt = 0;
            while (tb < tn && sb < sn) {
                if (source[sb] == target[tb]) {
                    ++cnt;
                    ++tb;
                }

                ++sb;
            }

            if (cnt > 0) {
                ++ans;
                i = tb - 1;

            } else {
                return -1;
            }
        }

        return ans;
    }
public:
    int shortestWay(string source, string target) {
        return by_two_ptr(source, target);
        
        //return by_binary_search(source, target);
    }
};