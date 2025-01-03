/*
Given a string s. In one step you can insert any character at any index of the string.

Return the minimum number of steps to make s palindrome.

A Palindrome String is one that reads the same backward as well as forward.

 

Example 1:

Input: s = "zzazz"
Output: 0
Explanation: The string "zzazz" is already palindrome we do not need any insertions.

Example 2:

Input: s = "mbadm"
Output: 2
Explanation: String can be "mbdadbm" or "mdbabdm".

Example 3:

Input: s = "leetcode"
Output: 5
Explanation: Inserting 5 characters the string becomes "leetcodocteel".

*/

class Solution {
private:
    int recursive(std::string& s, int left, int right, std::vector<std::vector<int>>& mem) {
        if (left >= right) {
            return 0;
        }

        if (mem[left][right] != -1) {
            return mem[left][right];
        }

        if (s[left] == s[right]) {
            mem[left][right] = recursive(s, left + 1, right - 1, mem);
        } else {
            //the plus 1 here means you meet difference and need to insert one to create palindrome, 
            //then you need to continue to find common substring
            mem[left][right] = 1 + std::min(recursive(s, left + 1, right, mem), 
                                        recursive(s, left, right - 1, mem));
        }

        return mem[left][right];
    }
public:
    int minInsertions(string s) {
        std::vector<std::vector<int>> mem(s.size(), std::vector<int>(s.size(), -1));

        return recursive(s, 0, s.size() - 1, mem);
    }
};
