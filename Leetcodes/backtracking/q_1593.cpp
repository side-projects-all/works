/*
Given a string s, return the maximum number of unique substrings that the given string can be split into.

You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.

A substring is a contiguous sequence of characters within a string.

 

Example 1:

Input: s = "ababccc"
Output: 5
Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.

Example 2:

Input: s = "aba"
Output: 2
Explanation: One way to split maximally is ['a', 'ba'].

Example 3:

Input: s = "aa"
Output: 1
Explanation: It is impossible to split the string any further.

 

Constraints:

    1 <= s.length <= 16

    s contains only lower case English letters.


*/

class Solution {
public:
    int maxUniqueSplit(string s) {
        std::unordered_set<std::string> existed;
        int max_cnt = 0;
        backtracking(s, existed, 0, 0, max_cnt);

        return max_cnt;
    }

private:
    void backtracking(const string& s, std::unordered_set<std::string>& existed, int i, int cnt, int& max_cnt) {
        if (cnt + (s.size() - i) <= max_cnt) {
            return;
        }

        if (i == s.size()) {
            max_cnt = std::max(max_cnt, cnt);
            return;
        }

        for (int e = i + 1; e <= s.size(); ++e) {
            std::string str = s.substr(i, e - i);

            if (existed.find(str) == existed.end()) {
                existed.insert(str);

                backtracking(s, existed, e, cnt + 1, max_cnt);

                existed.erase(str);
            }
        }
    }
};