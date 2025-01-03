/*
You are playing a Flip Game with your friend.

You are given a string currentState that contains only '+' and '-'. You and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move, and therefore the other person will be the winner.

Return all possible states of the string currentState after one valid move. You may return the answer in any order. If there is no valid move, return an empty list [].

 

Example 1:

Input: currentState = "++++"
Output: ["--++","+--+","++--"]

Example 2:

Input: currentState = "+"
Output: []

 

Constraints:

    1 <= currentState.length <= 500
    currentState[i] is either '+' or '-'.


*/

class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        std::vector<std::string> ans;
        int N = currentState.size();
        for (int i = 1; i < N; ++i) {
            if (currentState[i - 1] == '+' && currentState[i] == '+') {
                ans.push_back(currentState.substr(0, i - 1) + "--" + currentState.substr(i + 1, N - i));
            }
        }

        return ans;
    }
};