/*
Alice and Bob continue their games with piles of stones.  There are a number of piles arranged in a row, and each pile has a positive integer number of stones piles[i].  The objective of the game is to end with the most stones. 

Alice and Bob take turns, with Alice starting first.  Initially, M = 1.

On each player's turn, that player can take all the stones in the first X remaining piles, where 1 <= X <= 2M.  Then, we set M = max(M, X).

The game continues until all the stones have been taken.

Assuming Alice and Bob play optimally, return the maximum number of stones Alice can get.

 

Example 1:

Input: piles = [2,7,9,4,4]
Output: 10
Explanation:  If Alice takes one pile at the beginning, Bob takes two piles, then Alice takes 2 piles again. Alice can get 2 + 4 + 4 = 10 piles in total. If Alice takes two piles at the beginning, then Bob can take all three piles left. In this case, Alice get 2 + 7 = 9 piles in total. So we return 10 since it's larger. 

Example 2:

Input: piles = [1,2,3,4,5,100]
Output: 104

 

Constraints:

    1 <= piles.length <= 100
    1 <= piles[i] <= 10^4


*/

class Solution {
private:
    int recursive(vector<int>& piles) {
        int N = piles.size();
        std::vector<std::vector<std::vector<int>>> mem(2, 
            std::vector<std::vector<int>>(N + 1, std::vector<int>(N + 1, -1)));

        //p: 0 is Alice, 1 is Bob, m: the limitation M, i: index now
        std::function<int(int, int, int)> recurr = [&](int p, int m, int i) -> int {
            if (i == N) {
                return 0;
            }

            if (mem[p][m][i] != -1) {
                return mem[p][m][i];
            }

            int ans = (p == 0) ? -1 : 1000001;
            int sum = 0;
            for (int x = 1; x <= std::min(2 * m, N - i); ++x) {
                sum += piles[i + x - 1];

                if (p == 0) {
                    ans = std::max(ans, sum + recurr(1, std::max(x, m), i + x));
                } else {
                    ans = std::min(ans, recurr(0, std::max(x, m), i + x));
                }
            }

            return mem[p][m][i] = ans;
        };

        return recurr(0, 1, 0);
    }
public:
    int stoneGameII(vector<int>& piles) {
        return recursive(piles);
    }
};