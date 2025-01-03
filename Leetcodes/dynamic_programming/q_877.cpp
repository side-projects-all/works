/*
Alice and Bob play a game with piles of stones. There are an even number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].

The objective of the game is to end with the most stones. The total number of stones across all the piles is odd, so there are no ties.

Alice and Bob take turns, with Alice starting first. Each turn, a player takes the entire pile of stones either from the beginning or from the end of the row. This continues until there are no more piles left, at which point the person with the most stones wins.

Assuming Alice and Bob play optimally, return true if Alice wins the game, or false if Bob wins.

 

Example 1:

Input: piles = [5,3,4,5]
Output: true
Explanation: 
Alice starts first, and can only take the first 5 or the last 5.
Say she takes the first 5, so that the row becomes [3, 4, 5].
If Bob takes 3, then the board is [4, 5], and Alice takes 5 to win with 10 points.
If Bob takes the last 5, then the board is [3, 4], and Alice takes 4 to win with 9 points.
This demonstrated that taking the first 5 was a winning move for Alice, so we return true.

Example 2:

Input: piles = [3,7,2,3]
Output: true

 

Constraints:

    2 <= piles.length <= 500
    piles.length is even.
    1 <= piles[i] <= 500
    sum(piles[i]) is odd.


*/

class Solution {
private:
    bool iterative(vector<int>& piles) {
        int N = piles.size();
        int mem[N + 2][N + 2];
        memset(mem, 0, sizeof(mem));

        for (int size = 1; size <= N; ++size) {
            for (int i = 0, j = size - 1; j < N; ++i, ++j) {

                /*
                total number of piles picked = i - 0 + N - 1 - j = i + N - 1 - j, 
                and if (i + N - 1 - j) % 2 == 0, then it is Bob's turn. 
                The expression could be simplified as (i + N - j) % 2 == 1, 
                and be further optimized to (i + N + j) % 2 == 1.
                it looks nicer but harder to understand.
                */
                int turn = (j + i + N) % 2;

                if (turn == 1) {
                    mem[i + 1][j + 1] = std::max(piles[i] + mem[i + 2][j + 1], piles[j] + mem[i + 1][j]);
                } else {
                    mem[i + 1][j + 1] = std::min(-piles[i] + mem[i + 2][j + 1], -piles[j] + mem[i + 1][j]);
                }
            }
        }

        return mem[1][N] > 0;
    }
    bool recursive(vector<int>& piles) {
        return true;
    }
public:
    bool stoneGame(vector<int>& piles) {
        //return recursive(piles);
        return iterative(piles);
    }
};