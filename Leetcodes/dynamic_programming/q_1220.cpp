/*
Given an integer n, your task is to count how many strings of length n can be formed under the following rules:

    Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
    Each vowel 'a' may only be followed by an 'e'.
    Each vowel 'e' may only be followed by an 'a' or an 'i'.
    Each vowel 'i' may not be followed by another 'i'.
    Each vowel 'o' may only be followed by an 'i' or a 'u'.
    Each vowel 'u' may only be followed by an 'a'.

Since the answer may be too large, return it modulo 10^9 + 7.

 

Example 1:

Input: n = 1
Output: 5
Explanation: All possible strings are: "a", "e", "i" , "o" and "u".

Example 2:

Input: n = 2
Output: 10
Explanation: All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi", "ou" and "ua".

Example 3: 

Input: n = 5
Output: 68


Constraints:

    1 <= n <= 2 * 10^4
*/

class Solution {
private:
    int iterative_space_optimize(int n) {
        std::vector<long> vowels(5, 1);

        int MOD = 1'000'000'007;

        for (int i = 1; i < n; ++i) {
            long aNew = (vowels[1] + vowels[2] + vowels[4]) % MOD;
            long eNew = (vowels[0] + vowels[2]) % MOD;
            long iNew = (vowels[1] + vowels[3]) % MOD;
            long oNew = vowels[2];
            long uNew = (vowels[2] + vowels[3]) % MOD;

            vowels[0] = aNew;
            vowels[1] = eNew;
            vowels[2] = iNew;
            vowels[3] = oNew;
            vowels[4] = uNew;

        }

        long result = (vowels[0] + vowels[1] + vowels[2] + vowels[3] + vowels[4]) % MOD;
        return static_cast<int>(result);
    }

    int iterative(int n) {
        std::vector<std::vector<long>> mem(5, std::vector<long>(n, 0));

        for (int i = 0; i < 5; ++i) {
            mem[i][0] = 1L;
        }

        int MOD = 1'000'000'007;

        //0: a, 1: e, 2: i, 3: o, 4: u
        for (int i = 1; i < n; ++i) {
            //'a' comes from e, i, and u
            mem[0][i] = (mem[1][i - 1] + mem[2][i - 1] + mem[4][i - 1]) % MOD;
            //'e' comes from a, i
            mem[1][i] = (mem[0][i - 1] + mem[2][i - 1]) % MOD;
            //'i' comes from e, o
            mem[2][i] = (mem[1][i - 1] + mem[3][i - 1]) % MOD;
            //'o' comes from i
            mem[3][i] = mem[2][i - 1];
            //'u' comes from i, o
            mem[4][i] = (mem[2][i - 1] + mem[3][i - 1]) % MOD;
        }

        long result = 0L;

        for (int i = 0; i < 5; ++i) {
            result += mem[i][n - 1];
        }

        result = result % MOD;

        return static_cast<int>(result);
    }

    //i: vowel, n: the character index
    long recursive(int n, std::vector<std::vector<long>>& mem, int i, int MOD) {
        //base case, only one character, so only one permutation
        if (n == 0) {
            mem[n][i] = 1;
            return mem[n][i];
        }

        if (mem[n][i] != -1) {
            return mem[n][i];
        }

        //0: a, 1: e, 2: i, 3: o, 4: u
        //based on the rules( but in reverse way to think about the reaulationship) 
        //to do recursion,
        if (i == 0) {
            //'a' comes from e, i, and u
            mem[n][i] = (recursive(n - 1, mem, 1, MOD) + 
                            recursive(n - 1, mem, 2, MOD) + 
                                recursive(n - 1, mem, 4, MOD)) % MOD;
        } else if (i == 1) {
            //'e' comes from ea, i
            mem[n][i] = (recursive(n - 1, mem, 0, MOD) + 
                            recursive(n - 1, mem, 2, MOD)) % MOD;
        } else if (i == 2) {
            //'i' comes from e, o
            mem[n][i] = (recursive(n - 1, mem, 1, MOD) + 
                            recursive(n - 1, mem, 3, MOD)) % MOD;
        } else if (i == 3) {
            //'o' comes from i
            mem[n][i] = recursive(n - 1, mem, 2, MOD);
        }else if (i == 4) {
            //'u' comes from i, o
            mem[n][i] = (recursive(n - 1, mem, 2, MOD) + 
                                recursive(n - 1, mem, 3, MOD)) % MOD;
        }

        return mem[n][i];
    }
public:
    int countVowelPermutation(int n) {
        /*
        int MOD = 1'000'000'007;
        std::vector<std::vector<long>> mem(n, std::vector<long>(5, -1L));

        //i is the 5 vowels a, e, i, o, u
        long result = 0;
        for (int i = 0; i < 5; ++i) {
            result = (result + recursive(n - 1, mem, i, MOD)) % MOD;
        }

        return static_cast<int>(result);
        */

        //return iterative(n);
        return iterative_space_optimize(n);
    }
};