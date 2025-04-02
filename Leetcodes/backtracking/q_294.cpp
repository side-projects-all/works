/*
You are playing a Flip Game with your friend.

You are given a string currentState that contains only '+' and '-'. You and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move, and therefore the other person will be the winner.

Return true if the starting player can guarantee a win, and false otherwise.

 

Example 1:

Input: currentState = "++++"
Output: true
Explanation: The starting player can guarantee a win by flipping the middle "++" to become "+--+".

Example 2:

Input: currentState = "+"
Output: false

 

Constraints:

    1 <= currentState.length <= 60
    currentState[i] is either '+' or '-'.

*/

class Solution {
private:
    bool recursive(std::string&& s, std::unordered_map<std::string, int>& m) {
        if (m.find(s) != m.end()) {
            return m[s];
        }
        for (int i = 1; i < s.size(); ++i) {
            if (s[i - 1] == '+' && s[i] == '+') {

                s[i - 1] = '-';
                s[i] = '-';
                
                bool sec_win = recursive(std::move(s), m);

                s[i - 1] = '+';
                s[i] = '+';

                if (!sec_win) {
                    return m[s] = true;
                }
            }
        }

        return m[s] =false;
    }
    bool by_back_tracking(string& currentState) {
        std::unordered_map<std::string, int> m;
        return recursive(std::move(currentState), m);
    }
public:
    bool canWin(string currentState) {
        return by_back_tracking(currentState);
    }
};