/*
Given a string s, return all the palindromic permutations (without duplicates) of it.

You may return the answer in any order. If s has no palindromic permutation, return an empty list.

 

Example 1:

Input: s = "aabb"
Output: ["abba","baab"]

Example 2:

Input: s = "abc"
Output: []

 

Constraints:

    1 <= s.length <= 16
    s consists of only lowercase English letters.


*/

class Solution {
private:
    void backtracking(std::string& tmp, std::unordered_map<char, int>& m, 
                            std::vector<std::string>& ans, char mid, int left, int right) {
        
        //if the length of the string is even, left will cross right, and we do not need mid in this case
        if (left > right) {
            ans.push_back(tmp);
            return;
        }

        //if the length of the string is odd, left will meet right, then the mid will be used
        if (left == right) {
            tmp[left] = mid;
            ans.push_back(tmp);
            return;
        }

        for (auto& [key, val] : m) {
            if (val > 0) {
                tmp[left] = key;
                tmp[right] = key;

                val -= 2;

                backtracking(tmp, m, ans, mid, left + 1, right - 1);

                val += 2;
            }
        }
    }
public:
    vector<string> generatePalindromes(string s) {
        int n = s.size();
        std::vector<std::string> ans;

        if (n == 0) {
            return ans;
        }

        if (n == 1) {
            return { s };
        }

        std::unordered_map<char, int> m;
        for (char c : s) {
            ++m[c];
        }

        int odd_cnt = 0;
        char mid;
        for (auto& [key, val] : m) {
            if (val & 1) {
                ++odd_cnt;
                mid = key;
                --val;
            }

            if (odd_cnt > 1) {
                return {};
            }
        }

        std::string tmp(n, '0');
        backtracking(tmp, m, ans, mid, 0, n - 1);

        return ans;
    }
};