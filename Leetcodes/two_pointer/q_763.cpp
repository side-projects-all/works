/*
You are given a string s. We want to partition the string into as many parts as possible so that each letter appears in at most one part. For example, the string "ababcc" can be partitioned into ["abab", "cc"], but partitions such as ["aba", "bcc"] or ["ab", "ab", "cc"] are invalid.

Note that the partition is done so that after concatenating all the parts in order, the resultant string should be s.

Return a list of integers representing the size of these parts.

 

Example 1:

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits s into less parts.

Example 2:

Input: s = "eccbbbbdec"
Output: [10]

 

Constraints:

    1 <= s.length <= 500
    s consists of lowercase English letters.


*/

class Solution {
private:
    vector<int> by_two_ptr(string& s) {
        int n = s.size();
        std::vector<int> last_occur(26);
        for (int i = 0; i < n; ++i) {
            last_occur[s[i] - 'a'] = i;
        }

        int e = 0;
        int b = 0;
        std::vector<int> ans;
        for (int i = 0; i < n; ++i) {
            e = std::max(e, last_occur[s[i] - 'a']);

            if (i == e) {
                ans.push_back(i - b + 1);
                b = i + 1;
            }
        }

        return ans;
    }
public:
    vector<int> partitionLabels(string s) {
        return by_two_ptr(s);
    }
};