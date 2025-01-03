/*
Android devices have a special lock screen with a 3 x 3 grid of dots. Users can set an "unlock pattern" by connecting the dots in a specific sequence, forming a series of joined line segments where each segment's endpoints are two consecutive dots in the sequence. A sequence of k dots is a valid unlock pattern if both of the following are true:

    All the dots in the sequence are distinct.
    If the line segment connecting two consecutive dots in the sequence passes through the center of any other dot, the other dot must have previously appeared in the sequence. No jumps through the center non-selected dots are allowed.
        For example, connecting dots 2 and 9 without dots 5 or 6 appearing beforehand is valid because the line from dot 2 to dot 9 does not pass through the center of either dot 5 or 6.
        However, connecting dots 1 and 3 without dot 2 appearing beforehand is invalid because the line from dot 1 to dot 3 passes through the center of dot 2.

Here are some example valid and invalid unlock patterns:

    The 1st pattern [4,1,3,6] is invalid because the line connecting dots 1 and 3 pass through dot 2, but dot 2 did not previously appear in the sequence.
    The 2nd pattern [4,1,9,2] is invalid because the line connecting dots 1 and 9 pass through dot 5, but dot 5 did not previously appear in the sequence.
    The 3rd pattern [2,4,1,3,6] is valid because it follows the conditions. The line connecting dots 1 and 3 meets the condition because dot 2 previously appeared in the sequence.
    The 4th pattern [6,5,4,1,9,2] is valid because it follows the conditions. The line connecting dots 1 and 9 meets the condition because dot 5 previously appeared in the sequence.

Given two integers m and n, return the number of unique and valid unlock patterns of the Android grid lock screen that consist of at least m keys and at most n keys.

Two unlock patterns are considered unique if there is a dot in one sequence that is not in the other, or the order of the dots is different.

 

Example 1:

Input: m = 1, n = 1
Output: 9

Example 2:

Input: m = 1, n = 2
Output: 65

 

Constraints:

    1 <= m, n <= 9


*/

class Solution {
public:
    int numberOfPatterns(int m, int n) {
        int jump[10][10] = { 0 };

        jump[1][3] = jump[3][1] = 2;
        jump[4][6] = jump[6][4] = 5;
        jump[7][9] = jump[9][7] = 8;
        jump[1][7] = jump[7][1] = 4;
        jump[2][8] = jump[8][2] = 5;
        jump[3][9] = jump[9][3] = 6;
        jump[1][9] = jump[9][1] = jump[3][7] = jump[7][3] = 5;

        int visited_nums = 0;
        int total = 0;
        int dp[10][1 << 10] = { 0 };
        memset(dp, -1, sizeof(dp));

        total += recursive(1, 1, m, n, jump, visited_nums, dp) * 4;
        total += recursive(2, 1, m, n, jump, visited_nums, dp) * 4;
        total += recursive(5, 1, m, n, jump, visited_nums, dp);


        return total;
    }

private:
    int recursive(int curr_num, int curr_len, int min_len, int max_len, int jump[10][10], 
                    int visited_nums, int dp[10][1 << 10]) {

        if (curr_len > max_len) {
            return 0;
        }

        if (dp[curr_num][visited_nums] != -1) {
            return dp[curr_num][visited_nums];
        }

        int valid_ptn = 0;
        if (curr_len >= min_len) {
            ++valid_ptn;
        }

        visited_nums = set_bit(visited_nums, curr_num);

        for (int next_num = 1; next_num <= 9; ++next_num) {
            int jump_over = jump[curr_num][next_num];

            if (!is_set(visited_nums, next_num) && (jump_over == 0 || is_set(visited_nums, jump_over))) {
                valid_ptn += recursive(next_num, curr_len + 1, min_len, max_len, jump, visited_nums, dp);
            }
        }

        visited_nums = clear_bit(visited_nums, curr_num);

        return dp[curr_num][visited_nums] = valid_ptn;
    }

    int set_bit(int num, int pos) {
        num |= 1 << (pos - 1);

        return num;
    }

    int clear_bit(int num, int pos) {
        num ^= 1 << (pos - 1);

        return num;
    }

    bool is_set(int num, int pos) {
        int bit_pos = (num >> (pos - 1)) & 1;

        return bit_pos == 1;
    }
};