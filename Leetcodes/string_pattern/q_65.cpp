/*
A valid number can be split up into these components (in order):

    A decimal number or an integer.
    (Optional) An 'e' or 'E', followed by an integer.

A decimal number can be split up into these components (in order):

    (Optional) A sign character (either '+' or '-').
    One of the following formats:
        One or more digits, followed by a dot '.'.
        One or more digits, followed by a dot '.', followed by one or more digits.
        A dot '.', followed by one or more digits.

An integer can be split up into these components (in order):

    (Optional) A sign character (either '+' or '-').
    One or more digits.

For example, all the following are valid numbers: ["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"], while the following are not valid numbers: ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].

Given a string s, return true if s is a valid number.

 

Example 1:

Input: s = "0"
Output: true

Example 2:

Input: s = "e"
Output: false

Example 3:

Input: s = "."
Output: false

 

Constraints:

    1 <= s.length <= 20
    s consists of only English letters (both uppercase and lowercase), digits (0-9), plus '+', minus '-', or dot '.'.


*/

class Solution {
private:
    //Deterministic Finite Automaton
    bool dfa(string& s) {
        std::vector<std::unordered_map<std::string, int>> dfa;
        dfa.push_back({ {"digit", 1}, {"sign", 2}, {"dot", 3} });
        dfa.push_back({ {"digit", 1}, {"dot", 4}, {"exponent", 5} });
        dfa.push_back({ {"digit", 1}, {"dot", 3} });
        dfa.push_back({ {"digit", 4} });
        dfa.push_back({ {"digit", 4}, {"exponent", 5} });
        dfa.push_back({ {"sign", 6}, {"digit", 7} });
        dfa.push_back({ {"digit", 7} });
        dfa.push_back({ {"digit", 7} });

        std::unordered_set<int> validFinalState = {1, 4, 7};

        int currState = 0;
        std::string group = "";

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];

            if (std::isdigit(c)) {
                group = "digit";

            } else if (c == '+' || c == '-') {
                group = "sign";

            } else if (c == 'e' || c == 'E') {
                group = "exponent";
                
            } else if (c == '.') {
                group = "dot";
                
            } else {
                
                return false;
            }

            if (dfa[currState].find(group) == dfa[currState].end()) {
                return false;
            }

            currState = dfa[currState][group];
        }


        return validFinalState.find(currState) != validFinalState.end();
    }
    bool follow_rule(string& s) {
        bool hasDigit = false;
        bool oneExp = false;
        bool oneDot = false;

        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];

            if (std::isdigit(c)) {
                hasDigit = true;

            } else if (c == '+' || c == '-') {

                //not exponential sign
                if (i > 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
                    return false;
                }
            } else if (c == 'e' || c == 'E') {
                if (oneExp || !hasDigit) {
                    return false;
                }

                oneExp = true;
                hasDigit = false;

            } else if (c == '.') {
                if (oneDot || oneExp) {
                    return false;
                }

                oneDot = true;
            } else {
                return false;
            }
        }

        return hasDigit;
    }

public:
    bool isNumber(string s) {
        
        return follow_rule(s);
        //return dfa(s);
    }
};