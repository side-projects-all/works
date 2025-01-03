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
        int MOD = 1'000'000'007;
        if (n <= 2) {
            return n;
        }

        long f[n + 1];
        long p[n + 1];

        f[0] = 1L;
        f[1] = 1L;
        f[2] = 2L;
        p[2] = 1L;
        p[1] = 0L;
        for (int k = 3; k < n + 1; ++k) {
            f[k] = (f[k - 1] + f[k - 2] + 2 * p[k - 1]) % MOD;
            p[k] = (p[k - 1] + f[k - 2]) % MOD;
        }

        return static_cast<int>(f[n]);
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