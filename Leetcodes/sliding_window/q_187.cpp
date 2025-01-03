/*
The DNA sequence is composed of a series of nucleotides abbreviated as 'A', 'C', 'G', and 'T'.

    For example, "ACGAATTCCG" is a DNA sequence.

When studying DNA, it is useful to identify repeated sequences within the DNA.

Given a string s that represents a DNA sequence, return all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. You may return the answer in any order.

 

Example 1:

Input: s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT"
Output: ["AAAAACCCCC","CCCCCAAAAA"]

Example 2:

Input: s = "AAAAAAAAAAAAA"
Output: ["AAAAAAAAAA"]

 

Constraints:

    1 <= s.length <= 10^5
    s[i] is either 'A', 'C', 'G', or 'T'.


*/

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        int len = 10;
        int n = s.size();
        std::unordered_set<std::string> seen;
        std::unordered_set<std::string> ans;

        for (int i = 0; i < n - len + 1; ++i) {
            std::string t = s.substr(i, len);

            if (seen.find(t) != seen.end()) {
                ans.insert(t);
            }

            seen.insert(t);
        }

        return std::vector<std::string>(ans.begin(), ans.end());
    }
};