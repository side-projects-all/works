/*
You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.

Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7.

In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.

Example 1:

Input: n = 3
Output: 5
Explanation: The five different ways are show above.

Example 2:

Input: n = 1
Output: 1

Constraints:

    1 <= n <= 1000


*/

class Solution {
private:
    int iterative(int n) {
        if (n == 1) {
            return 1;
        }

        if (n == 2) {
            return 2;
        }

        std::vector<unsigned int> full(n + 1);
        std::vector<unsigned int> partial(n + 1);
        full[1] = 1;
        full[2] = 2;
        partial[2] = 1;

        for (int i = 3; i <= n; ++i) {
            full[i] += (full[i - 2] + full[i - 1] + 2 * partial[i - 1]) % 1'000'000'007;
            partial[i] += (full[i - 2] + partial[i - 1]) % 1'000'000'007;
        }
        
        return full[n];
    }

    long recursive_p(int n, int MOD, std::vector<long>& f, std::vector<long>& p) {
        if (n == 2) {
            return 1L;
        }

        if (p[n] != -1) {
            return p[n];
        }

        long val = 0L;
        val  = (recursive_p(n - 1, MOD, f, p) + recursive_f(n - 2, MOD, f, p)) % MOD;

        p[n] = val;

        return val;
    }

    long recursive_f(int n, int MOD, std::vector<long>& f, std::vector<long>& p) {
        if (n == 1) {
            return 1L;
        } else if (n == 2) {
            return 2L;
        }

        if (f[n] != -1) {
            return f[n];
        }

        long val = 0L;
        //for example, 
        //f(3) = f(3 - 1) + f(3 - 2) + 2 * p(3 - 1)
        //it means full tiles board of 2x3 could be formed by these three ways, 
        //and you count all those sub-cases, then you will total combinations
        val  = (recursive_f(n - 1, MOD, f, p) + 
                        recursive_f(n - 2, MOD, f, p) + 
                            2 * recursive_p(n - 1, MOD, f, p)) % MOD;

        f[n] = val;

        return val;
    }
public:
    int numTilings(int n) {
        //memoization for: 
        //fully tiled
        //std::vector<long> f(n + 1, -1);

        //partially tiled
        //std::vector<long> p(n + 1, -1);
        
        //return static_cast<int>(recursive_f(n, 1'000'000'007, f, p));
        return iterative(n);
    }
};