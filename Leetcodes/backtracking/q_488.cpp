/*
You are playing a variation of the game Zuma.

In this variation of Zuma, there is a single row of colored balls on a board, where each ball can be colored red 'R', yellow 'Y', blue 'B', green 'G', or white 'W'. You also have several colored balls in your hand.

Your goal is to clear all of the balls from the board. On each turn:

    Pick any ball from your hand and insert it in between two balls in the row or on either end of the row.
    If there is a group of three or more consecutive balls of the same color, remove the group of balls from the board.
        If this removal causes more groups of three or more of the same color to form, then continue removing each group until there are none left.
    If there are no more balls on the board, then you win the game.
    Repeat this process until you either win or do not have any more balls in your hand.

Given a string board, representing the row of balls on the board, and a string hand, representing the balls in your hand, return the minimum number of balls you have to insert to clear all the balls from the board. If you cannot clear all the balls from the board using the balls in your hand, return -1.

 

Example 1:

Input: board = "WRRBBW", hand = "RB"
Output: -1
Explanation: It is impossible to clear all the balls. The best you can do is:
- Insert 'R' so the board becomes WRRRBBW. WRRRBBW -> WBBW.
- Insert 'B' so the board becomes WBBBW. WBBBW -> WW.
There are still balls remaining on the board, and you are out of balls to insert.

Example 2:

Input: board = "WWRRBBWW", hand = "WRBRW"
Output: 2
Explanation: To make the board empty:
- Insert 'R' so the board becomes WWRRRBBWW. WWRRRBBWW -> WWBBWW.
- Insert 'B' so the board becomes WWBBBWW. WWBBBWW -> WWWW -> empty.
2 balls from your hand were needed to clear the board.

Example 3:

Input: board = "G", hand = "GGGGG"
Output: 2
Explanation: To make the board empty:
- Insert 'G' so the board becomes GG.
- Insert 'G' so the board becomes GGG. GGG -> empty.
2 balls from your hand were needed to clear the board.

 

Constraints:

    1 <= board.length <= 16
    1 <= hand.length <= 5
    board and hand consist of the characters 'R', 'Y', 'B', 'G', and 'W'.
    The initial row of balls on the board will not have any groups of three or more consecutive balls of the same color.


*/

class Solution {
private:
    inline void make_key(std::size_t& seed, const std::string& board, const std::string& hand) const {
        std::hash<std::string> hasher;
        seed ^= hasher(board) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        seed ^= hasher(hand) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    void cancel_consecutive_balls(string& board) {
        int b = 0;
        while (b < board.size()) {
            int e = b;
            while (e < board.size() && board[b] == board[e]) {
                ++e;
            }

            if (e - b >= 3) {
                board.erase(board.begin() + b, board.begin() + e);
                b = 0;
            } else {
                ++b;
            }
        }
    }
    int recursive(string&& board, string&& hand, std::unordered_map<std::size_t, int>& mem) {
        if (board.empty()) {
            return 0;
        }

        if (hand.empty()) {
            return INT_MAX;
        }

        std::size_t key = 0;
        make_key(key, board, hand);
        if (mem.find(key) != mem.end()) {
            return mem[key];
        }

        int ans = INT_MAX;
        for (int i = 0; i < hand.size(); ++i) {

            if (i > 0 && hand[i - 1] == hand[i]) {
                continue;   //for performance improvement
            }
            for (int j = 0; j < board.size(); ++j) {

                if ((hand[i] == board[j]) || (j > 0 && board[j - 1] == board[j] && hand[i] != board[j])) {

                    std::string new_board = board.substr(0, j) + hand[i] + board.substr(j);
                    std::string new_hand = hand.substr(0, i) + hand.substr(i + 1);
                    cancel_consecutive_balls(new_board);

                    int tmp = recursive(std::move(new_board), std::move(new_hand), mem);
                    if (tmp != INT_MAX) {
                        ans = std::min(ans, 1 + tmp);
                    }
                }
            }
        }

        return mem[key] = ans;
    }
    int by_recursive_dp(string& board, string& hand) {
        std::unordered_map<std::size_t, int> mem;
        std::sort(hand.begin(), hand.end());    //for performance improvement
        int ans = recursive(std::move(board), std::move(hand), mem);
        return ans != INT_MAX ? ans : -1;
    }
public:
    int findMinStep(string board, string hand) {
        return by_recursive_dp(board, hand);
    }
};