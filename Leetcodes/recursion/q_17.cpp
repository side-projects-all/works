/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

 

Example 1:

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:

Input: digits = ""
Output: []

Example 3:

Input: digits = "2"
Output: ["a","b","c"]

 

Constraints:

    0 <= digits.length <= 4
    digits[i] is a digit in the range ['2', '9'].


*/

class Solution {
private:
    void backtracking(string& digits, std::unordered_map<char, std::string>& m, 
                        std::vector<std::string>& ans, std::string& curr, int i) {
        if (curr.size() == digits.size()) {
            ans.push_back(curr);
        }

        for (char c : m[digits[i]]) {
            curr.push_back(c);
            backtracking(digits, m, ans, curr, i + 1);
            curr.pop_back();
        }
    }
    vector<string> by_backtracking(string& digits) {
        if (digits.empty()) {
            return {};
        }
        std::vector<std::string> ans;
        std::unordered_map<char, std::string> m{{'2', "abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, 
                                                        {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9', "wxyz"}};

        std::string curr{""};
        backtracking(digits, m, ans, curr, 0); 
        return ans;
    }
public:
    vector<string> letterCombinations(string digits) {
        return by_backtracking(digits);
    }
};